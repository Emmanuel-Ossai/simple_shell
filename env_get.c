#include "myshell.h"

/**
 * get_environ - a C function that shows environ
 * @info: the struct data
 * Return: 0
 **/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = string_n_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


/**
 * _unsetenv - a C function that unset variables of environment
 * @info: the struct data
 * @var: environment variable
 *  Return: 0 or 1
 **/
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = del_indx(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->env_changed);
}


/**
 * _setenv - a C function that sets a variable for an environment
 * @info: the struct data
 * @var: environment variable
 * @value: value of environment variable
 *  Return: 0
 **/
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	string_copy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_add_ext(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
