#include "shell.h"

/**
 * shell_myenv- prints the current environment
 * @infoo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shell_myenv(info_t *infoo)
{
	print_list_str(infoo->env);
	return (0);
}

/**
 * *shell_getenv - gets the value of an environ variable
 * @infoo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *shell_getenv(info_t *infoo, const char *name)
{
	list_t *node = infoo->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * shell_mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infoo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_mysetenv(info_t *infoo)
{
	if (infoo->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infoo, infoo->argv[1], infoo->argv[2]))
		return (0);
	return (1);
}

/**
 * shell_myunsetenv - Remove an environment variable
 * @infoo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_myunsetenv(info_t *infoo)
{
	int i;

	if (infoo->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infoo->argc; i++)
		_unsetenv(infoo, infoo->argv[i]);

	return (0);
}

/**
 * shell_populate_env_list - populates env linked list
 * @infoo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shell_populate_env_list(info_t *infoo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	infoo->env = node;
	return (0);
}
