#include "shell.h"

/**
 **shell_strncpy - copies a string
 *@dests: the destination string to be copied to
 *@srcs: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *shell_strncpy(char *dests, char *srcs, int y)
{
	int i, j;
	char *s = dests;

	i = 0;
	while (srcs[i] != '\0' && i < y - 1)
	{
		dests[i] = srcs[i];
		i++;
	}
	if (i < y)
	{
		j = i;
		while (j < y)
		{
			dests[j] = '\0';
			j++;
		}
	}
	return (s);
}

/*
 **shell_strncat - concatenates two strings
 *@dests: the first string
 *@srcs: the second string
 *@y: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *shell_strncat(char *dests, char *srcs, int y)
{
	int i, j;
	char *s = dests;

	i = 0;
	j = 0;
	while (dests[i] != '\0')
		i++;
	while (srcs[j] != '\0' && j < y)
	{
		dests[i] = srcs[j];
		i++;
		j++;
	}
	if (j < y)
		dests[i] = '\0';
	return (s);
}

/*
 **shell_strchr - locates a character in a string
 *@c: the string to be parsed
 *@s: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *shell_strchr(char *s, char c)
{
    while (*s != '\0') {
        if (*s == c)
            return s;
        s++; 
    }
    return NULL;
}
