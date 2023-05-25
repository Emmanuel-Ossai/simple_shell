#include "myshell.h"

/**
 * convert_number - a C function that convert number
 * @num: the number to be converted
 * @base: base of the conversion
 * @flags: the flags
 * Return: convertee
 **/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long z = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		z = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[z % base];
		z /= base;
	} while (z != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * print_d - a C function that function print decimal numbers
 * @input: input number
 * @fd: the filedescriptor
 * Return: printed numbers
 **/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			count++;
		}
		current %= x;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * print_error - a C function that prints error response
 * @info: the struct data
 * @estr: errored string
 * Return: 0, -1
 **/
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 * uncomment - a C function that remove comments
 * @buf: the buffer address
 * Return: 0
 **/
void uncomment(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
