#include "libmx.h"

void *mx_realloc(void *ptr, size_t size)
{
    if (!size)
    {
        free(ptr);
        return NULL;
    }
    void *new = malloc(size);

    if (!new)
        return NULL;
    if(ptr)
        mx_memcpy(new, ptr, size);
    return new;
}
