#include "myshell.h"

/**
 * buffer_input - a C function that buffers commands
 * @info: the struct data
 * @buf: the buffer
 * @len: length variable
 * Return: buffer
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			uncomment(*buf);
			history_built(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}


/**
 * _input_catch - a C function that show a line
 * @info: the struct data
 * Return: line
 **/
ssize_t _input_catch(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buffer_input(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		y = x;
		p = buf + x;

		chain_chekd(info, buf, &y, x, len);
		while (y < len)
		{
			if (chain_conf(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}


/**
 * read_buf - a C function that checks and read buffer
 * @info: the struct data
 * @buf: the buffer
 * @x: the size
 *
 * Return: read value
 **/
ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
	ssize_t r = 0;

	if (*x)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*x = r;
	return (r);
}


/**
 * _getline - a C function that checks and gets the next line of input
 * @info: the struct data
 * @ptr: the pointer to the buffer
 * @length: the size of buffer
 * Return: next line of input
 **/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len)
		x = len = 0;
r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + x, k - x);
	else
		_strncpy(new_p, buf + x, k - x + 1);

	s += k - x;
	x = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * sigintHandler - a C function that blocks ctrl-C
 * @sig_num: the signal
 * Return: none
 **/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
