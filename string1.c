#include "shell.h"

/**
 * _strcpy - copies a string
 * @dests: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dests, char *src)
{
	int i = 0;

	if (dests == src || src == 0)
		return (dests);
	while (src[i])
	{
		dests[i] = src[i];
		i++;
	}
	dests[i] = 0;
	return (dests);
}

/**
 * _strdup - duplicates a string
 * @strs: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *strs)
{
	int length = 0;
	char *ret;

	if (strs == NULL)
		return (NULL);
	while (*strs++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--strs;
	return (ret);
}

/**
 *_puts - prints an input string
 *@strs: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strs)
{
	int i = 0;

	if (!strs)
		return;
	while (strs[i] != '\0')
	{
		_putchar(strs[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @x: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char x)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}
