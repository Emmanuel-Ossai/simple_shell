#include "myshell.h"

/**
 * chain_conf - a C function that test if character in a buffer
 * is a chain delimeter
 * @info: the struct data
 * @buf: the buffer
 * @p: the position
 * Return: 0 or 1
 **/
int chain_conf(info_t *info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = y;
	return (1);
}


/**
 * chain_chekd - a C function that checks chain
 * @info: the struct data
 * @buf: the buffer
 * @p: the position
 * @i: starting position in buffer
 * @len: length of buffer
 * Return: none
 **/
void chain_chekd(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


/**
 * alias_change - a C function that replaces an alias in the tokenized string
 * @info: the struct data
 * Return: 0 or 1
 **/
int alias_change(info_t *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = prefix_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = duplicate_str(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * vars_change - a C function that replaces vars in tokenized string
 * @info: the struct data
 * Return: 0 or 1
 **/
int vars_change(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					duplicate_str(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					duplicate_str(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = prefix_node(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
					duplicate_str(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], duplicate_str(""));

	}
	return (0);
}

/**
 * replace_string - a C function that replaces string
 * @old: old string
 * @new: new string
 * Return: 0 or 1
 **/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
