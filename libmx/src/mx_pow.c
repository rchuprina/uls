#include "libmx.h"

double mx_pow(double n, unsigned int pow)
{
    if (!n && pow)
        return 0;
    if (!pow)
        return 1;
    return n * mx_pow(n, pow - 1);
}
