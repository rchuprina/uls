#include "libmx.h"

char *mx_strndup(const char *s1, size_t n)
{
    if (!s1)
        return NULL;
    int len = mx_strlen(s1);

    if (len < n)
        n = len;
    return mx_strncpy(mx_strnew(n), s1, n);
}
