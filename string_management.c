#include "myshell.h"

/**
 * _strlen - a C function that checks and returns the length of string
 * @s: the string
 * Return: length of string
 **/
int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _strcmp - a C function that compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: the integer
 **/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * starts_with - a C function that checks for needle starts
 * @haystack: string to search for
 * @needle: needle string
 * Return: char of haystack
 **/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}


/**
 * _strcat - a C funtion that concatenates two strings
 * @dest: the destination
 * @src: the source
 * Return: pointer to buffer
 **/
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
