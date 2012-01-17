#include <gpod/itdb.h>

char *track_destination(char *dest, Itdb_Track *track, char *root);
void transfer_from_ipod(Itdb_iTunesDB *db, char *root);
void transfer_track_from_ipod(Itdb_Track *track, char *root);
