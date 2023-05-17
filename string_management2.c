#include "myshell.h"

/**
 * string_copy - a C function that copies strings
 * @dest: the destination
 * @src: the source
 * Return: dest
 **/
char *string_copy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}


/**
 * duplicate_str - a C function that duplicate strings
 * @str: the string
 * Return: duplicate
 **/
char *duplicate_str(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - a C funtion that print input strings
 * @str: the string
 * Return: none
 **/
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}


/**
 * _putchar - a C function that write the character c to standard output
 * @c: the character c
 * Return: 1
 **/
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
