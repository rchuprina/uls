#include "libmx.h"

void mx_swap_void(void **a, void **b)
{
    void *c = *a;
    *a = *b;
    *b = c;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *))
{
    if (!lst)
        return NULL;
    for (t_list *i = lst; i->next; i = i->next)
    {
        for (t_list *j = i->next; j; j = j->next)
        {
            if ((*cmp)(i->data, j->data))
                mx_swap_void(&i->data, &j->data);
        }
    }
    return lst;
}

