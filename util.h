#include <sys/types.h>
#define ALLOC_FAIL(s) cpod_error("could not allocate %d bytes\n", s)
#define MALLOC(p, s, action) \
    do { p = calloc(1, s); if(!p) {ALLOC_FAIL(s); action; } } while(0)
#define FREE(ptr) do { free((void *)ptr); ptr = NULL; } while (0)

void cpod_error(const char *, ...);
int cp(const char *, const char *);
int mkdir_p(const char *, mode_t);
