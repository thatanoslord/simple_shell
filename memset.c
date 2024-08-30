#include "shell.h"

/**
 **shell_memset - fills memory with a constant byte
 *@c: the pointer to the memory area
 *@x: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *shell_memset(char *c, char x, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		c[i] = x;
	return (c);
}

/**
 * shell_ffree - frees a string of strings
 * @px: string of strings
 */
void shell_ffree(char **px)
{
	char **a = px;

	if (!px)
		return;
	while (*px)
		free(*px++);
	free(a);
}

/**
 * *shell_realloc - reallocates a block of memory
 * @ptrs: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *shell_realloc(void *ptrs, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptrs)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptrs), NULL);
	if (new_size == old_size)
		return (ptrs);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptrs)[old_size];
	free(ptrs);
	return (p);
}
