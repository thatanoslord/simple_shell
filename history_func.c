#include "shell.h"

/**
 * *shell_get_history_file - gets the history file
 * @infoo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *shell_get_history_file(info_t *infoo)
{
	char *buf, *dir;

	dir = _getenv(infoo, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * shell_write_history - creates a file, or appends to an existing file
 * @infoo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int shell_write_history(info_t *infoo)
{
	ssize_t fd;
	char *filename = get_history_file(infoo);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = infoo->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * shell_read_history - reads history from file
 * @infoo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int shell_read_history(info_t *infoo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infoo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(infoo, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(infoo, buf + last, linecount++);
	free(buf);
	infoo->histcount = linecount;
	while (infoo->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infoo->history), 0);
	renumber_history(infoo);
	return (infoo->histcount);
}

/**
 * shell_build_history_list - adds entry to a history linked list
 * @infoo: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int shell_build_history_list(info_t *infoo, char *buf, int linecount)
{
	list_t *node = NULL;

	if (infoo->history)
		node = infoo->history;
	add_node_end(&node, buf, linecount);

	if (!infoo->history)
		infoo->history = node;
	return (0);
}

/**
 * shell_renumber_history - renumbers the history linked list after changes
 * @infoo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int shell_renumber_history(info_t *infoo)
{
	list_t *node = infoo->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (infoo->histcount = i);
}
