#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @infoo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *infoo)
{
	print_list(infoo->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @infoo: parameter struct
 * @strs: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *infoo, char *strs)
{
	char *p, c;
	int ret;

	p = _strchr(strs, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(infoo->alias),
		get_node_index(infoo->alias, node_starts_with(infoo->alias, strs, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @infoo: parameter struct
 * @strs: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *infoo, char *strs)
{
	char *p;

	p = _strchr(strs, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(infoo, strs));

	unset_alias(infoo, strs);
	return (add_node_end(&(infoo->alias), strs, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @infoo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *infoo)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (infoo->argc == 1)
	{
		node = infoo->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infoo->argv[i]; i++)
	{
		p = _strchr(infoo->argv[i], '=');
		if (p)
			set_alias(infoo, infoo->argv[i]);
		else
			print_alias(node_starts_with(infoo->alias, infoo->argv[i], '='));
	}

	return (0);
}
