#include "include/list.h"

void	list_init(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	return;
}

void	list_destroy(List *list)
{
	void	*data;

	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL)
			list->destroy(data);
	}
	return;
}

int	list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt	*new_element = malloc(sizeof(ListElmt));

	if (new_element == NULL)
		return (-1);
	new_element->data = (void *)data;
	if (element == NULL) {
		if (list_size(list) == 0)
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	else {
		if (element->next == NULL)
			list->tail == new_element;
		new_element->next = element->next;
		element->next = new_element;
	}
	list->size++;
	return (0);
}

int	list_rem_next(List *list, ListElmt *element, void **data)
{
	ListElmt	*old_element;

	if (list_size(list) == 0)
		return (-1);
	if (element == NULL) {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;
		if (list_size(list) == 1)
			list->tail = NULL;
	}
	else {
		if (element->next == NULL)
			return (-1);
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;
		if (element->next == NULL)
			list->tail = element;
	}
	free(old_element);
	list->size--;
	return (0);
}

void	element_destroy(void *data)
{
	if (data != NULL)
		free(data);
	return;
}

int	main(void)
{
	List	*list = malloc(sizeof(List));
	char	*string_1 = strdup("string_1");
	char	*string_2 = strdup("string_2");
	void	(*destroy)(void *) = &element_destroy;
	void	*freed_data;


	list_init(list, destroy);
	list_ins_next(list, NULL, (void *)string_1);
	list_ins_next(list, NULL, (void *)string_2);
	list_rem_next(list, list->head, &freed_data);
	printf("String '%s' was removed and freed.\n", (char *)freed_data);
	list_destroy(list);
	free(freed_data);
	free(list);
	return (0);
}
