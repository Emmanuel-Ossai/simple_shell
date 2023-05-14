#include "myshell.h"

/**
 * clear_info - a C function that start info_t struct
 * @info: the struct data
 * Return: none
 **/
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


/**
 * set_info - a C function that sets info_t struct
 * @info: the struct data
 * @av: the argument vector
 * Return: none
 **/
void set_info(info_t *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = _string_t(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_str(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;

		alias_change(info);
		vars_change(info);
	}
}


/**
 * free_info - a C function that free info_t struct
 * @info: the struct data
 * @all: all fields
 * Return: none
 **/
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			list_freed(&(info->env));
		if (info->history)
			list_freed(&(info->history));
		if (info->alias)
			list_freed(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
