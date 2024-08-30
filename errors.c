#include "shell.h"

/**
 *_eputs - prints an input string
 * @strr: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *strr)
{
	int i = 0;

	if (!strr)
		return;
	while (strr[i] != '\0')
	{
		_eputchar(strr[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fdd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fdd)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdd, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @strr: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *strr, int fdd)
{
	int i = 0;

	if (!strr)
		return (0);
	while (*strr)
	{
		i += _putfd(*strr++, fdd);
	}
	return (i);
}
