#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gpod/itdb.h>
#include <glib.h>

#include "util.h" //cp(from, to)

char *track_destination(char *dest, Itdb_Track *track, char *root) {
    /* Hard code this for now. in the future, I would like to have some sort of
     * printf-like setup eventually...
     * REMEMBER TO free() IT!
     */
    sprintf(dest, "%s/%s/%s/%s.mp3",
            root, track->artist, track->album, track->title);
}
    

void transfer_from_ipod(Itdb_iTunesDB *db, char *root) {
    GList *elem = NULL;
    Itdb_Track *track;

    for (elem = db->tracks; elem; elem = elem->next) {
        track = elem->data;
        int ret = transfer_track_from_ipod(track, root);
        if (ret)
            WAS HERE WHEN I WENT TO SLEEP
    }
}

int transfer_track_from_ipod(Itdb_Track *track, char *root) {
    char *from = itdb_filename_on_ipod(track);
    size_t len = strlen(root) + strlen(track->artist) + strlen(track->album)
               + strlen(track->title) + strlen(".mp3") +3/*slashes*/+1/*\0*/;
    char *to = malloc(len);
    destination_for(to, track, root);
    int ret = cp(from, to);
    free(to);
    g_free(filename);
    return ret;
}
