#include "myshell.h"

/**
 * is_cmd - a C function that verify and confirm an executable command
 * @info: the struct data
 * @path: the path of file
 * Return: 0 or 1
 **/
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * dup_chars - a c function that duplicate characters
 * @pathstr: the string path
 * @start: the start of the index
 * @stop: the stop of the index
 * Return: buffer
 **/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, k = 0;

	for (k = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[k++] = pathstr[x];
	buf[k] = 0;
	return (buf);
}

/**
 * path_check - a C function that checks file path
 * @info: the struct data
 * @pathstr: the path string
 * @cmd: the cmd
 * Return: full path of cmd
 */
char *path_check(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = dup_chars(pathstr, curr_pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}
