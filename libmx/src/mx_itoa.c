#include "libmx.h"

char *mx_itoa(int number)
{
    int cn = number;
    int size = 1;
    int count = 1;
    char *itoa = NULL;

    if (number < 0)
        size++;
    while (cn > 9 || cn < -9)
    {
        cn /= 10;
        size++;
        count *= 10;
    }
    itoa = mx_strnew(size);
    for (int i = 0; i < size; i++)
    {
        if (number < 0  && !i)
            itoa[i] = '-';
        else
        {
            if (number < 0)
                itoa[i] = number / count * -1 + 48;
            else
                itoa[i] = number / count + 48;
            number %= count;
            count /= 10;
        }
    }
    return itoa;
}
