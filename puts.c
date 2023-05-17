#include "myshell.h"

/**
 * _eputs - a C function write string
 * @str: the string
 * Return: none
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}


/**
 * _eputchar - a C function that write character c to standard error
 * @c: character c to write
 * Return: -1 or 1
 **/
int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}


/**
 * _puts_str - a C function that write input string
 * @str: the string
 * @fd: the filedescriptor
 * Return: character
 **/
int _puts_str(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}


/**
 * _putfd - a C function that write character c to file descriptor
 * @c: the character c
 * @fd: the filedescriptor
 * Return: -1, 1 or error
 **/
int _putfd(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

