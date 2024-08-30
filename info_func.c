#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @infoo: struct address
 */
void clear_info(info_t *infoo)
{
	infoo->arg = NULL;
	infoo->argv = NULL;
	infoo->path = NULL;
	infoo->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @infoo: struct address
 * @av: argument vector
 */
void set_info(info_t *infoo, char **av)
{
	int i = 0;

	infoo->fname = av[0];
	if (infoo->arg)
	{
		infoo->argv = strtow(infoo->arg, " \t");
		if (!infoo->argv)
		{

			infoo->argv = malloc(sizeof(char *) * 2);
			if (infoo->argv)
			{
				infoo->argv[0] = _strdup(infoo->arg);
				infoo->argv[1] = NULL;
			}
		}
		for (i = 0; infoo->argv && infoo->argv[i]; i++)
			;
		infoo->argc = i;

		replace_alias(infoo);
		replace_vars(infoo);
	}
}

/**
 * free_info - frees info_t struct fields
 * @infoo: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *infoo, int all)
{
	ffree(infoo->argv);
	infoo->argv = NULL;
	infoo->path = NULL;
	if (all)
	{
		if (!infoo->cmd_buf)
			free(infoo->arg);
		if (infoo->env)
			free_list(&(infoo->env));
		if (infoo->history)
			free_list(&(infoo->history));
		if (infoo->alias)
			free_list(&(infoo->alias));
		ffree(infoo->environ);
			infoo->environ = NULL;
		bfree((void **)infoo->cmd_buf);
		if (infoo->readfd > 2)
			close(infoo->readfd);
		_putchar(BUF_FLUSH);
	}
}
