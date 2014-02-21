#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "util.h"

void cpod_error(const char *errformat, ...) {
    va_list args;
    char format[256]; /* plenty of space */
    sprintf(format, "cpod: %s\n", errformat);
    vfprintf(stderr, format, args);
    va_end(args);
}

int cp(const char *to, const char *from)
{
    int fd_to, fd_from;
    char buf[4096];
    ssize_t nread;
    int saved_errno;

    fd_from = open(from, O_RDONLY);
    if (fd_from < 0)
        return -1;

    fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0)
        goto out_error;

    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(fd_to, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                goto out_error;
            }
        } while (nread > 0);
    }

    if (nread == 0)
    {
        if (close(fd_to) < 0)
        {
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);

        /* Success! */
        return 0;
    }

  out_error:
    saved_errno = errno;

    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);

    errno = saved_errno;
    return -1;
}

int mkdirp(char *directory, mode_t mask) {
#ifdef _WIN32
    int result = mkdir(directory);
	if (result == 0) chmod(directory, mask);
#else
    int result = mkdir(directory, mask);
#endif
    if (result == 0) return 0;
    if (errno == EEXIST) {
        cpod_error("%s: %s", directory, strerror(EEXIST));
        return -1;
    } else if (errno == ENOENT) {
        char* last_slash = strrchr(directory, '/');
        if (last_slash == NULL) {
            cpod_error("%s: %s", directory, strerror(errno));
            return -1;
        }
        *last_slash = 0;
        if (!mkdirp(directory, mask)) return 1;
        *last_slash = '/';
#ifdef _WIN32
        result = mkdir(directory);
        if (result == 0) chmod(directory, mask);
#else
        result = mkdir(directory, mask);
#endif
        if (result == 0) return 0;
        if (errno == EEXIST) {
           return -1;
        }
        cpod_error("%s: %s", directory, strerror(errno));
        return -1;
    } else {
        cpod_error("%s: %s", directory, strerror(errno));
        return -1;
    }
}
