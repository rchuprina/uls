#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len)
{
    if (!little_len)
        return (unsigned char *)big;
    for (size_t i = 0; i < big_len; i++)
    {
        if (((unsigned char *)big)[i] == ((unsigned char *)little)[0])
        {
            size_t j = 0;
            while (((unsigned char *)big)[i + j] == ((unsigned char *)little)[j] && i + j < big_len && j < little_len)
                j++;
            if (j == little_len)
                return &((unsigned char *)big)[i];
        }
    }
    return NULL;
}

