#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @ss: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *ss)
{
	int i = 0;

	if (!ss)
		return (0);

	while (*ss++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @a1: the first strang
 * @a2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *a1, char *a2)
{
	while (*a1 && *a2)
	{
		if (*a1 != *a2)
			return (*a1 - *a2);
		a1++;
		a2++;
	}
	if (*a1 == *a2)
		return (0);
	else
		return (*a1 < *a2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystacks: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystacks, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystacks++)
			return (NULL);
	return ((char *)haystacks);
}

/**
 * _strcat - concatenates two strings
 * @dests: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dests, char *src)
{
	char *ret = dests;

	while (*dests)
		dests++;
	while (*src)
		*dests++ = *src++;
	*dests = *src;
	return (ret);
}
