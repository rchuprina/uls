#include "libmx.h"

void mx_printint(int n)
{
    int cn = n;
    int count = 1;

    if (n < 0)
        mx_printchar('-');
    while (cn > 9 || cn < -9)
    {
        cn /= 10;
        count *= 10;
    }
    while (count)
    {
        if (n < 0)
            mx_printchar(n / count * -1 + 48);
        else
            mx_printchar(n / count + 48);
        n %= count;
        count /= 10;
    }
}
