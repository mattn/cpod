#include <stdbool.h>
#include <gpod/itdb.h>
#include <id3tag.h>

#ifndef CPOD_DB_H
#define CPOD_DB_H

Itdb_iTunesDB *itdb_from_pl(char *);
Itdb_Track *track_parse(char *, Itdb_iTunesDB *);
bool is_ipod_mountpoint(char *);

#endif
