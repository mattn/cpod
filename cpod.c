#include <stdio.h> /* sprintf, vfprintf, printf */
#include <stdarg.h> /* va_list */
#include <stdbool.h> /* booleans */
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

    if (argv[1] == NULL) {
        cpod_error("too few arguments");
        return 1;
    }

    puts("loading database from .pl file...");
    db = itdb_from_pl(argv[1]);
    puts("database loaded.");

    if (is_ipod_mountpoint(argv[2])) {
        itdb_set_mountpoint(db, argv[2]);
    } else {
        cpod_error("there is no iPod at %s", argv[2]);
        return 1;
    }

    puts("transferring dat db");
    transfer_db(db);
    puts("done.");

    itdb_free(db);
    return 0;
}
