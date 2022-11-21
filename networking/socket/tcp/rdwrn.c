#include <unistd.h>
#include <errno.h>
#include "rdwrn.h"

ssize_t
readn(int fd, void *buffer, size_t n)
{
    ssize_t num_read;
    size_t total_read;
    char *buf;

    buf = buffer;

    for (total_read = 0; total_read < n; )
    {
        num_read = read(fd, buf, n - total_read);

        if (num_read == 0)
        {
            return total_read;
        }
        if (num_read == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }

        buf += num_read;
        total_read += num_read;
    }
    return total_read;
}

ssize_t 
writen(int fd, const void *buffer, size_t n)
{
    ssize_t num_writen;
    size_t total_writen;
    const char *buf;

    buf = buffer;

    for (total_writen = 0; total_writen < n; )
    {
        num_writen = write(fd, buf, n-total_writen);

        if (num_writen <= 0)
        {
            if (num_writen == -1 && errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }
        total_writen += num_writen;
        buf += num_writen;
    }

    return total_writen;
}

