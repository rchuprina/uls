#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle)
{
    while (*haystack)
    {
        if (*haystack == *needle)
        {
            char *p = (char *)haystack;
            char *p2 = (char *)needle;

            while (*haystack == *needle && *haystack)
            {
                haystack++;
                needle++;
            }
            if (!(*needle))
                return p;
            needle = p2;
        }
        haystack++;
    }
    return NULL;
}
