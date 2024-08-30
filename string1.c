#include "shell.h"

/**
 * *shell_strcpy - copies a string
 * @dests: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *shell_strcpy(char *dests, char *src)
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
 * *shell_strdup - duplicates a string
 * @strs: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *shell_strdup(const char *strs)
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
 *shell_puts - prints an input string
 *@strs: the string to be printed
 *
 * Return: Nothing
 */
void shell_puts(char *strs)
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
 * shell_putchar - writes the character c to stdout
 * @x: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int shell_putchar(char x)
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
