#include "myshell.h"

/**
 * bfree - a C funtion that free pointer and address
 * @ptr: the pointer to be freed
 * Return: 0 or 1
 **/
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


/**
 * _memset - a C function that sets a memory with byte
 * @s: memory area
 * @b: size in byte
 * @n: number of bytes
 * Return: area set
 **/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}
