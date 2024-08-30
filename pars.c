#include "shell.h"

/**
 * shell_is_cmd - determines if a file is an executable command
 * @infoo: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int shell_is_cmd(info_t *infoo, char *path)
{
	struct stat st;

	(void)infoo;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * *shell_dup_chars - duplicates characters
 * @pathstrr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *shell_dup_chars(char *pathstrr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstrr[i] != ':')
			buf[k++] = pathstrr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * *shell_find_path - finds this cmd in the PATH string
 * @infoo: the info struct
 * @pathstrr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *shell_find_path(info_t *infoo, char *pathstrr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstrr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(infoo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrr[i] || pathstrr[i] == ':')
		{
			path = dup_chars(pathstrr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(infoo, path))
				return (path);
			if (!pathstrr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
