#include <stdio.h> /* sprintf, vfprintf, printf */
#include <stdarg.h> /* va_list */
#include <gpod/itdb.h> /* Itdb_* structs */

#include "cpod.h"
#include "db.h"

void cpod_error(char *errformat, ...) {
    va_list args;
    char format[256]; /* plenty of space */
    sprintf(format, "cpod: %s\n", errformat);
    vfprintf(stderr, format, args);
    va_end(args);
}

int main(int argc, char *argv[]) {
    Itdb_iTunesDB *db = NULL;
    Itdb_Track *track = NULL;
    GList *e = NULL;

    if (argv[1] == NULL) {
        cpod_error("too few arguments");
        return 1;
    }
    db = itdb_from_pl(argv[1]);
    
    for (e = db->tracks; e; e = e->next) {
        track = (Itdb_Track *)(e->data);
        printf("%s by %s\n", track->title, track->artist);
    }
    itdb_free(db);
    return 0;
}
