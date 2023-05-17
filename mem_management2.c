#include "myshell.h"

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


/**
 * ffree - a C function that frees strings
 * @pp: string of strings
 **/
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - a C function that reallocates memory blocks
 * @ptr: pointer to mem
 * @old_size: previous size
 * @new_size: new size
 * Return: new block
 **/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
