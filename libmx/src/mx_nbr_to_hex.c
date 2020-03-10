#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr)
{
    int size = 1;
    unsigned long cnbr = nbr / 16;
    char chex[17] = "0123456789abcdef\0";
    char *hex;

    while (cnbr)
    {
        cnbr /= 16;
        size++;
    }
    hex = mx_strnew(size);
    for (int i = size - 1; i >= 0; --i)
    {
        hex[i] = chex[nbr % 16];
        nbr /= 16;
    }
    return hex;
}
