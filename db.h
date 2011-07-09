#include <stdbool.h>
#include <gpod/itdb.h>
#include <id3tag.h>

#ifndef CPOD_DB_H
#define CPOD_DB_H

Itdb_iTunesDB *itdb_get(char *path);
Itdb_iTunesDB *itdb_from_pl(char *path);
Itdb_Track *track_parse(char *path);
bool transfer_db(Itdb_iTunesDB *db);
bool is_ipod_mountpoint(char *mp);

#endif
