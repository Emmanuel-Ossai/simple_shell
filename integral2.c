#include "myshell.h"

/**
 * _history - a C function that shows history list
 * @info: the struct data
 *  Return: 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - a C function that unsets alias
 * @info: the struct data
 * @str: alias of the string
 * Return: 1 or 0
 **/
int unset_alias(info_t *info, char *str)
{
        char *c, d;
        int ret;

        c = _strchr(str, '=');
        if (!c)
                return (1);
        d = *c;
        *c = 0;
        ret = del_indx(&(info->alias),
                node_ind_check(info->alias, prefix_node(info->alias, str, -1)));
        *c = d;
        return (ret);
}

/**
 * set_alias - a C function that sets alias
 * @info: the struct data
 * @str: alias of the string
 *
 * Return: 1 or 0
 **/
int set_alias(info_t *info, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (_add_ext(&(info->alias), str, 0) == NULL);
}


/**
 * alias_print - a C function that shows alias
 * @node: the node
 * Return: 0
 **/
int alias_print(list_t *node)
{
	char *c = NULL, *a = NULL;

	if (node)
	{
		c = _strchr(node->str, '=');
		for (a = node->str; a <= c; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _alias - a C functions that performs similarly to alias function
 * @info: the struct data
 *  Return: 0
 **/
int _alias(info_t *info)
{
	int x = 0;
	char *c = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		c = _strchr(info->argv[x], '=');
		if (c)
			set_alias(info, info->argv[x]);
		else
			alias_print(prefix_node(info->alias, info->argv[x], '='));
	}

	return (0);
}

