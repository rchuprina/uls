#include "libmx.h"

void mx_pop_back(t_list **head)
{
    if (*head)
    {
        if ((*head)->next)
        {
            t_list *p = *head;

            while (p->next->next)
                p = p->next;
            free(p->next);
            p->next = NULL;
        }
        else
        {
            free(*head);
            *head = NULL;
        }
    }
}

