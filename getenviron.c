#include "shell.h"

/**
 * **shell_get_environ - returns the string array copy of our environ
 * @infoo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **shell_get_environ(info_t *infoo)
{
	if (!infoo->environ || infoo->env_changed)
	{
		infoo->environ = list_to_strings(infoo->env);
		infoo->env_changed = 0;
	}

	return (infoo->environ);
}

/**
 * shell_unsetenv - Remove an environment variable
 * @infoo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int shell_unsetenv(info_t *infoo, char *var)
{
	list_t *node = infoo->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			infoo->env_changed = delete_node_at_index(&(infoo->env), i);
			i = 0;
			node = infoo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infoo->env_changed);
}

/**
 * shell_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infoo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int shell_setenv(info_t *infoo, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = infoo->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			infoo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infoo->env), buf, 0);
	free(buf);
	infoo->env_changed = 1;
	return (0);
}
