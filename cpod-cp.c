#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <gpod/itdb.h>

#include "db.h"
#include "util.h"

int main(int argc, char *argv[]) {
    Itdb_iTunesDB *db = NULL;
    GError *err = NULL;
    char *mp = NULL;
    char *local_path = NULL;

    if (argc != 3 || !is_ipod_mountpoint(argv[2])) {
        fprintf(stderr, "usage: cpod-cp <file> <ipod mountpoint>\n");
        return 1;
    }

    mp = argv[2];
    local_path = argv[1];

    db = itdb_parse(mp, &err);
    if (err) goto error_exit;

    Itdb_Track *track = track_parse(local_path, db);
    track->itdb = db;
    itdb_cp_track_to_ipod(track, track->userdata, &err);

    itdb_write(db, &err);
    if (err) goto error_exit;
    itdb_free(db);
    db = NULL;
    return 0;

  error_exit:
    cpod_error(err->message);
    return 1;
}
