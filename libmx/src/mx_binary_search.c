#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count)
{
    int first = 0;
    int last = size - 1;
    int mid = 0;

    while (last >= first)
    {
        (*count)++;
        mid = (last + first) / 2;
        int num = mx_strcmp(arr[mid], s);
        if (!num)
            return mid;
        else if (num < 0)
            first = mid + 1;
        else if (num > 0)
            last = mid - 1;
    }
    *count = 0;
    return -1;
}
