#include "shell.h"

/**
 * shell_is_chain - test if current char in buffer is a chain delimeter
 * @infoo: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int shell_is_chain(info_t *infoo, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infoo->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infoo->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		infoo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * shell_check_chain - checks we should continue chaining based on last status
 * @infoo: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void shell_check_chain(info_t *infoo, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (infoo->cmd_buf_type == CMD_AND)
	{
		if (infoo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (infoo->cmd_buf_type == CMD_OR)
	{
		if (!infoo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * shell_replace_alias - replaces an aliases in the tokenized string
 * @infoo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int shell_replace_alias(info_t *infoo)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infoo->alias, infoo->argv[0], '=');
		if (!node)
			return (0);
		free(infoo->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infoo->argv[0] = p;
	}
	return (1);
}

/**
 * shell_replace_vars - replaces vars in the tokenized string
 * @infoo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int shell_replace_vars(info_t *infoo)
{
	int i = 0;
	list_t *node;

	for (i = 0; infoo->argv[i]; i++)
	{
		if (infoo->argv[i][0] != '$' || !infoo->argv[i][1])
			continue;

		if (!_strcmp(infoo->argv[i], "$?"))
		{
			replace_string(&(infoo->argv[i]),
				_strdup(convert_number(infoo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infoo->argv[i], "$$"))
		{
			replace_string(&(infoo->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infoo->env, &infoo->argv[i][1], '=');
		if (node)
		{
			replace_string(&(infoo->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infoo->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * shell_replace_string - replaces string
 * @old: address of old string
 * @news: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int shell_replace_string(char **old, char *news)
{
	free(*old);
	*old = news;
	return (1);
}
