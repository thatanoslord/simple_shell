#include "shell.h"

/**
 * shell_erratoi - converts a string to an integer
 * @x: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int shell_erratoi(char *x)
{
	int i = 0;
	unsigned long int result = 0;

	if (*x == '+')
		x++;  /* TODO: why does this make main return 255? */
	for (i = 0;  x[i] != '\0'; i++)
	{
		if (x[i] >= '0' && x[i] <= '9')
		{
			result *= 10;
			result += (x[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * shell_print_error - prints an error message
 * @infoo: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void shell_print_error(info_t *infoo, char *estr)
{
	_eputs(infoo->fname);
	_eputs(": ");
	print_d(infoo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infoo->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * shell_print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fdd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int shell_print_d(int input, int fdd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fdd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * shell_convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flag: argument flags
 *
 * Return: string
 */
char *shell_convert_number(long int num, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptrs;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrs = &buffer[49];
	*ptrs = '\0';

	do	{
		*--ptrs = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptrs = sign;
	return (ptrs);
}

/**
 * shell_remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void shell_remove_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
