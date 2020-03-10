#include "uls.h"

void mx_bsort(char **arr, int size, bool (*order)(int cmp))
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (order(mx_strcmp(arr[i], arr[j])))
            {
                mx_swap_str(&arr[i], &arr[j]);
            }
        }
    }
}
