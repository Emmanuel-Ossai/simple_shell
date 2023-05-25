#include "myshell.h"

/**
 * node_addition - a C function that performs addition of node to list
 * @head: the head node
 * @str: the string
 * @num: the index
 * Return: list
 **/
list_t *node_addition(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = duplicate_str(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}


/**
 * _add_ext - a C function that add node to list
 * @head: the head node
 * @str: the string
 * @num: the index
 * Return: list
 **/
list_t *_add_ext(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = duplicate_str(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * strlist_print - a C function that print string of a list
 * @h: the head node
 * Return: list
 **/
size_t strlist_print(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}


/**
 * del_indx - a C function that delete node at required index
 * @head: the head node
 * @index: the index
 * Return: 0 or 1
 **/
int del_indx(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}


/**
 * list_freed - a C function that frees nodes of a specified list
 * @head_ptr: the head node
 * Return: none
 **/
void list_freed(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
