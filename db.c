#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <gpod/itdb.h>
#include <taglib/tag_c.h>

#include "db.h"
#include "util.h"

/* get an Itdb_iTunesDB from a .pl file (a flat list of filenames) */
Itdb_iTunesDB *itdb_from_pl(char *path) {
    FILE *pl = fopen(path, "r");
    char track_path[2048];
    Itdb_Track *track = NULL;
    Itdb_iTunesDB *result = itdb_new();
    /* we use g_strdup so that the filename may be g_freed by itdb_free */
    result->filename = g_strdup(path);
    
    while (fgets(track_path, 2048, pl) != NULL) {
        /* chop newline */
        track_path[strlen(track_path)-1] = '\0';
        track = track_parse(track_path, result);
        itdb_track_add(result, track, -1);
    }
    return result;
}

/* get an Itdb_Track from the given file */
Itdb_Track *track_parse(char *path, Itdb_iTunesDB *db) {
    TagLib_File *file = NULL;
    TagLib_Tag *tag = NULL;
    const TagLib_AudioProperties *audio = NULL;
    Itdb_Track *track = itdb_track_new();

    FILE *track_file = fopen(path, "r");
    fseek(track_file, 0, SEEK_END);
    track->size = ftell(track_file);
    fclose(track_file);

    /* we are storing our filename in userdata */
    track->userdata = g_strdup(path);
    track->userdata_duplicate = (gpointer (*)(gpointer))g_strdup;
    track->userdata_destroy = g_free;

    track->transferred = FALSE;
    itdb_track_add(db, track, -1);

    file = taglib_file_new(path);
    if (file == NULL) {
        /* should this be an error? */
        cpod_error("error reading metadata from \"%s\"\n", path);
        return track;
    }
    tag = taglib_file_tag(file);
    audio = taglib_file_audioproperties(file);

    /* g_strdup() string fields so that taglib_tag_free_strings() works */
    track->title = g_strdup(taglib_tag_title(tag));
    track->album = g_strdup(taglib_tag_album(tag));
    track->artist = g_strdup(taglib_tag_artist(tag));
    track->genre = g_strdup(taglib_tag_genre(tag));
    track->comment = g_strdup(taglib_tag_comment(tag));
    track->track_nr = taglib_tag_track(tag);
    track->year = taglib_tag_year(tag);
    /* audioproperties_length is in seconds and track->tracklen is in ms */
    track->tracklen = taglib_audioproperties_length(audio) * 1000;
    track->samplerate = taglib_audioproperties_samplerate(audio);

    taglib_tag_free_strings();
    /* taglib_file_free() frees TagLib_{Tag,AudioProperties} too */
    taglib_file_free(file);

    return track;
}

/* check to see if a given path is an iPod mountpoint */
bool is_ipod_mountpoint(char *mp) {
    if (itdb_get_itunesdb_path(mp))
        return true;
    else
        return false;
}
