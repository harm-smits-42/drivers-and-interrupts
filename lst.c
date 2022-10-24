#include "keyloggger.h"

t_entry_lst *add_entry(t_entry_lst **lst, char *entry)
{
	t_entry_lst *new;
	t_entry_lst *curr = *lst;
	
	if (!lst || !(ret = kmalloc(sizeof(t_entry_lst), GFP_ATOMIC)))
		return NULL;
	
	new.entry = entry;
	new.next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;	
	}
	return *lst;
}

void del_lst(t_entry_lst *lst)
{
	t_lst *next;

	if (!lst)
		return;

	while (lst)
	{
		next = lst->next;
		kfree(lst);
		lst = next;
	}
}
