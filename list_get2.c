#include "myshell.h"

/**
 * list_len - a C function that checks length of list
 * @h: the head node
 * Return: list
 **/
size_t list_len(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * string_n_list - a C function that shows array of strings of list
 * @head: the head node
 * Return: string array
 **/
char **string_n_list(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), y;
	char **strs;
	char *str;

	if (!head || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = string_copy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}

/**
 * print_list - a C function that display the elements of a list
 * @h: the head node
 * Return: list
 **/
size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}


/**
 * prefix_node - a C function that shows string nodes with prefix
 * @node: the node
 * @prefix: the prefix
 * @c: the character
 * Return: 0
 **/
list_t *prefix_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * node_ind_check - a C function that checks index of a node
 * @head: the head node
 * @node: the node
 * Return: -1
 **/
ssize_t node_ind_check(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
