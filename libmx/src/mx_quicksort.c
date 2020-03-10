#include "libmx.h"

void mx_swap_str(char **s1, char **s2)
{
    char *str = *s1;
    *s1 = *s2;
    *s2 = str;
}

int mx_quicksort(char **arr, int left, int right)
{
    int sum = 0;
    if (!arr) return -1;
    if (left < right)
    {
        int first = left, last = right;
        char *middle = arr[(first + last) / 2];
        for (; mx_strlen(arr[first]) < mx_strlen(middle); first++);
        for (; mx_strlen(arr[last]) > mx_strlen(middle); last--);
        while (first <= last) {
            while (mx_strlen(arr[first]) < mx_strlen(middle)) 
                first++;
            while (mx_strlen(arr[last]) > mx_strlen(middle)) 
                last--;
            if (first <= last)
            {
                if (mx_strlen(arr[first]) != mx_strlen(arr[last]) 
                    && arr[first] != arr[last]) sum++;
                mx_swap_str(&arr[first], &arr[last]);
                first++;
                last--;
            }
        }
        sum += mx_quicksort(arr, left, last);
        sum += mx_quicksort(arr, first, right);
    }
    return sum;
}
