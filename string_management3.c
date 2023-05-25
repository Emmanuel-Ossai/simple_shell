#include "myshell.h"

/**
 * _string_t - a C function that splits a string into words
 * @str: input strings
 * @d: delimeter string
 * Return: array of strings
 **/
char **_string_t(char *str, char *d)
{
	int x, y, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) &&
				(is_delim(str[x + 1], d) || !str[x + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[x], d))
			x++;
		k = 0;
		while (!is_delim(str[x + k], d) && str[x + k])
			k++;
		s[x] = malloc((k + 1) * sizeof(char));
		if (!s[y])
		{
			for (k = 0; k < y; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[y][m] = str[x++];
		s[y][m] = 0;
	}
	s[y] = NULL;

	return (s);
}


/**
 *_string_t2 - a C function that splits a string into words
 * @str: the string
 * @d: delimeter
 * Return: string array
 **/
char **_string_t2(char *str, char d)
{
	int x, y, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		k = 0;
	s[y][m] = 0;

	while (str[x + k] != d && str[x + k] && str[x + k] != d)
		k++;
	s[y] = malloc((k + 1) * sizeof(char));

	if (!s[y])
	{
		for (k = 0; k < y; k++)
			free(s[k]);
		free(s);
		return (NULL);
	}
	for (m = 0; m < k; m++)
		s[y][m] = str[x++];
	}
	s[y] = NULL;

	return (s);
}
