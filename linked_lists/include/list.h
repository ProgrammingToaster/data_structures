#ifndef LIST_H_
# define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
** Linked lists structures
*/

typedef struct ListElmt_
{
	void			*data;
	struct ListElmt_*	next;
}	ListElmt;

typedef struct List_
{
	int			size;
	int			(*match)(const void *, const void *);
	void			(*destroy)(void *);
	ListElmt		*head;
	ListElmt		*tail;
}	List;

/*
** Functions declarations
*/

void	list_init(List *, void (*destroy)(void *));
void	list_destroy(List *);
int	list_ins_next(List *, ListElmt *, const void *);
int	list_rem_next(List *, ListElmt *, void **);

/*
** Useful macros for the linked lists structures
*/

# define list_size(list)		((list)->size)
# define list_head(list)		((list)->head)
# define list_tail(list)		((list)->tail)
# define list_is_head(list, element)	((element) == (list)->head ? 1 : 0)
# define list_is_tail(list, element)	((element) == (list)->tail ? 1 : 0)
# define list_data(element)		((element)->data)
# define list_next(element)		((element)->next)

#endif /* LIST_H_ */
