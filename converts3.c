#include "myshell.h"

/**
 **_strncpy - a C function that copy string
 *@dest: the destination
 *@src: the source
 *@n: the number of characters
 *Return: convertee
 **/
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}



/**
 **_strncat - a C function that concatenates strings
 *@dest: string 1
 *@src: string 2
 *@n: the number
 *Return: result of concatenation
 **/
char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (s);
}


/**
 **_strchr - a C function that finds character in strings
 *@s: the string
 *@c: the character
 *Return: found character
 **/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
