#include "libmx.h"

void mx_pop_front(t_list **head)
{
	if (*head)
	{
	    t_list *p = (*head)->next;

	    free(*head);
	    *head = p;
	}
}

