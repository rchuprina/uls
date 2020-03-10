#include "libmx.h"

int mx_file_len(const char *file)
{
    int fd = open(file, O_RDONLY);
    int len = 1;
    char buf = '\0';

    if (fd == -1)
    {
        close(fd);
        return -1;
    }
    if (read(fd, &buf, 1) <= 0)
    {
        close(fd);
        return -2;
    }
    while (read(fd, &buf, 1))
    	len++;
    close(fd);
    return len;
}

char *mx_file_to_str(const char *file)
{
    int fd = open(file, O_RDONLY);
    char buf = '\0';
    char *str = NULL;
    int len = mx_file_len(file);

    if (len < 0)
        return NULL;
    str = mx_strnew(len);
    fd = open(file, O_RDONLY);
    for (int i = 0; i < len; i++)
    {
        read(fd, &buf, 1);
        str[i] = buf;
    }
    close(fd);
    return str;
}

