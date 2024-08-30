#include "shell.h"

/**
 * shell_hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_rets = 0;

	while (r != -1 && builtin_rets != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_rets = find_builtin(info);
			if (builtin_rets == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_rets == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rets);
}

/**
 * shell_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int shell_find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbls[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbls[i].type; i++)
		if (_strcmp(info->argv[0], builtintbls[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbls[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * shell_find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void shell_find_cmd(info_t *infoo)
{
	char *path = NULL;
	int i, k;

	infoo->path = infoo->argv[0];
	if (infoo->linecount_flag == 1)
	{
		infoo->line_count++;
		infoo->linecount_flag = 0;
	}
	for (i = 0, k = 0; infoo->arg[i]; i++)
		if (!is_delim(infoo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infoo, _getenv(infoo, "PATH="), infoo->argv[0]);
	if (path)
	{
		infoo->path = path;
		fork_cmd(infoo);
	}
	else
	{
		if ((interactive(infoo) || _getenv(infoo, "PATH=")
			|| infoo->argv[0][0] == '/') && is_cmd(infoo, infoo->argv[0]))
			fork_cmd(infoo);
		else if (*(infoo->arg) != '\n')
		{
			infoo->status = 127;
			print_error(infoo, "not found\n");
		}
	}
}

/**
 * shell_fork_cmd - forks a an exec thread to run cmd
 * @infoo: the parameter & return info struct
 *
 * Return: void
 */
void shell_fork_cmd(info_t *infoo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infoo->path, infoo->argv, get_environ(infoo)) == -1)
		{
			free_info(infoo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infoo->status));
		if (WIFEXITED(infoo->status))
		{
			infoo->status = WEXITSTATUS(infoo->status);
			if (infoo->status == 126)
				print_error(infoo, "Permission denied\n");
		}
	}
}
