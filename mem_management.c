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
