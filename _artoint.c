#include "shell.h"

/**
 * my_interactive - returns true if shell is interactive mode
 * @infoo: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int my_interactive(info_t *infoo)
{
	return (isatty(STDIN_FILENO) && infoo->readfd <= 2);
}

/**
 * my_is_delim - checks if character is a delimeter
 * @x: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int my_is_delim(char x, char *delim)
{
	while (*delim)
		if (*delim++ == x)
			return (1);
	return (0);
}

/**
 *my_isalpha - checks for alphabetic character
 *@x: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int my_isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *my_atoi - converts a string to an integer
 *@e: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int my_atoi(char *e)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  e[i] != '\0' && flag != 2; i++)
	{
		if (e[i] == '-')
			sign *= -1;

		if (e[i] >= '0' && e[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (e[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
