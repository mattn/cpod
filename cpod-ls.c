#include <gpod/itdb.h>
#include <glib.h>
#include <stdio.h>

#include "db.h"
#include "util.h"

int main(int argc, char *argv[]) {
    Itdb_iTunesDB *db = NULL;
    GList *e = NULL;
    Itdb_Track *track = NULL;
    GError *err = NULL;

    if (argc != 2 || !is_ipod_mountpoint(argv[1])) {
        fprintf(stderr, "usage: cpod-ls <ipod mountpoint>\n");
        return 1;
    }

    db = itdb_parse(argv[1], &err);
    if (err) {
        cpod_error(err->message);
        return 1;
    }

    for (e = db->tracks; e; e = e->next) {
        track = (Itdb_Track *)(e->data);
        printf("%s by %s\n", track->title, track->artist);
    }
    itdb_free(db);
    return 0;
}
