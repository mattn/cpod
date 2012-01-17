#include <stdio.h> /* sprintf, vfprintf, printf */
#include <stdarg.h> /* va_list */
#include <stdbool.h> /* booleans */
#include <gpod/itdb.h> /* Itdb_* structs */

#include "cpod.h"
#include "db.h"
#include "transfer.h"

void cpod_error(char *errformat, ...) {
    va_list args;
    char format[256]; /* plenty of space */
    sprintf(format, "cpod: %s\n", errformat);
    vfprintf(stderr, format, args);
    va_end(args);
}

int main(int argc, char *argv[]) {
    Itdb_iTunesDB *db = NULL;
    GError *err = NULL;
    GList *element = NULL;

    if (argv[1] == NULL) {
        cpod_error("too few arguments");
        return 1;
    }

    db = itdb_parse(argv[1], &err);

    if (err) {
        cpod_error(err->message);
        return 1;
    }

    for (element = db->tracks; element; element = element->next) {
        Itdb_Track *track = element->data;
        char *filename = itdb_filename_on_ipod(track);
        puts(filename);
        g_free(filename);
    }

    itdb_free(db);
    return 0;
}
