#include "libmx.h"

static unsigned long dec(char c)
{
    if (c >= '0' && c <= '9')
        return c - 48;
    if (c >= 'a' && c <= 'f')
        return c - 87;
    if (c >= 'A' && c <= 'F')
        return c - 55;
    return 16;
}

unsigned long mx_hex_to_nbr(const char *hex)
{
    int i = 0;
    unsigned long num = 0;

    if (!hex)
        return 0;
    while (hex[i])
        i++;
    for (int j = 0; hex[j]; j++)
    {
        i--;
        unsigned long g = dec(hex[j]);
        if (g == 16)
            return 0;
        num += g * (unsigned long)mx_pow(16, i);
    }
    return num;
}
