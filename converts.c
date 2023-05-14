#include "myshell.h"

/**
 * synergy - a C function that verify if shell is interactive
 * @info: the struct data
 * Return: 1 or 0
 **/
int synergy(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - a C function that verify if a character is a delimeter
 * @c: the character to be verified
 * @delim: the delimeter
 * Return: 1 or 0
 **/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - a C function that verify if a character is alphabetic
 * @c: the character to be verified
 * Return: 1 or 0
 **/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - a C function that performs string to integer conversion
 * @s: the string
 * Return: 0 or conversion
 **/

int _atoi(char *s)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
