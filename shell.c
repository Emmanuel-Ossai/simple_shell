#include "myshell.h"

/**
 * hsh - the shell prompt program
 * @info: the struct data
 * @av: the argument vector
 * Return: 0 or 1
 **/
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (synergy(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = _input_catch(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = builtin_check(info);
			if (builtin_ret == -1)
				cmd_check(info);
		}
		else if (synergy(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!synergy(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}


/**
 * builtin_check - a C function that checks for builtin command
 * @info: the struct data
 * Return: -1, 0, 1 or 2
 */
int builtin_check(info_t *info)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[x].func(info);
			break;
		}
	return (built_in_ret);
}


/**
 * cmd_check - a C function that checks for a path in commands
 * @info: the struct data
 * Return: none
 **/
void cmd_check(info_t *info)
{
	char *path = NULL;
	int x, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, k = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			k++;
	if (!k)
		return;

	path = path_check(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((synergy(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - a C function that forks and exec thread process
 * @info: the struct data
 * Return: none
 **/
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
