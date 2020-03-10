#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len)
{
    char *s = mx_strndup(src, len);

    for (size_t i = 0; i < len; i++)
        ((unsigned char *)dst)[i] = s[i];
    mx_strdel(&s);
    return dst;
}

