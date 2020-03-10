#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n)
{
    int index = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (((unsigned char *)s)[i] == c)
            index = i;
    }
    if (index)
        return &((unsigned char *)s)[index];
    return NULL;
}
