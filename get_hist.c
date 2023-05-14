#include "myshell.h"

/**
 * check_hist - a C function that checks and gets history file
 * @info: the struct data
 * Return: history file
 **/

char *check_hist(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_copy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


/**
 * write_history - a C function that writes history file
 * @info: the struct data
 * Return: -1 or 1
 **/
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = check_hist(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puts_str(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}


/**
 * read_history - a C function that reads history file
 * @info: the struct data
 * Return: 0 or count
 **/
int read_history(info_t *info)
{
	int x, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = check_hist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			history_built(info, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		history_built(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del_indx(&(info->history), 0);
	hist_organize(info);
	return (info->histcount);
}


/**
 * history_built - a C function that add to history file
 * @info: the struct data
 * @buf: the buffer
 * @linecount: history count
 * Return: Always 0
 **/
int history_built(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_add_ext(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


/**
 * hist_organize - a C function that organize the history files
 * @info: the struct data
 * Return: history count
 **/
int hist_organize(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
