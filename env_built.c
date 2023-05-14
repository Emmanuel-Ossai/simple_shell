#include "myshell.h"

/**
 * _env - a C function that displays current environment
 * @info: the struct data
 * Return: 0
 */
int _env(info_t *info)
{
	strlist_print(info->env);
	return (0);
}

/**
 * _getenv - a C function that fetch variable of the environment
 * @info: the struct data
 * @name: the name of the environment variable
 * Return: the result
 **/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *c;

	while (node)
	{
		c = starts_with(node->str, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}


/**
 * _mysetenv - a C function that push a variable for new environment
 * @info: the struct data
 *  Return: 0
 **/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}


/**
 * _myunsetenv - a C function that unset environment variable
 * @info: the struct data
 * Return: 0
 **/
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}


/**
 * environ_list - a C function that shows list of environment variables
 * @info: the struct data
 * Return: 0
 **/
int environ_list(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		_add_ext(&node, environ[x], 0);
	info->env = node;
	return (0);
}
