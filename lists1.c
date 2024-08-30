#include "shell.h"

/**
 * shell_list_len - determines length of linked list
 * @s: pointer to first node
 *
 * Return: size of list
 */
size_t shell_list_len(const list_t *s)
{
	size_t i = 0;

	while (s)
	{
		s = s->next;
		i++;
	}
	return (i);
}

/**
 * **shell_list_to_strings - returns an array of strings of the list->str
 * @heads: pointer to first node
 *
 * Return: array of strings
 */
char **shell_list_to_strings(list_t *heads)
{
	list_t *node = heads;
	size_t i = list_len(heads), j;
	char **strs;
	char *str;

	if (!heads || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * shell_print_list - prints all elements of a list_t linked list
 * @a: pointer to first node
 *
 * Return: size of list
 */
size_t shell_print_list(const list_t *a)
{
	size_t i = 0;

	while (a)
	{
		_puts(convert_number(a->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		i++;
	}
	return (i);
}

/**
 * *shell_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @d: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *shell_node_starts_with(list_t *node, char *prefix, char d)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((d == -1) || (*p == d)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * shell_get_node_index - gets the index of a node
 * @heads: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t shell_get_node_index(list_t *heads, list_t *node)
{
	size_t i = 0;

	while (heads)
	{
		if (heads == node)
			return (i);
		heads = heads->next;
		i++;
	}
	return (-1);
}
