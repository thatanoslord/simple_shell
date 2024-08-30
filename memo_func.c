#include "shell.h"

/**
 * shell_bfree - frees a pointer and NULLs the address
 * @ptrs: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int shell_bfree(void **ptrs)
{
	if (ptrs && *ptrs)
	{
		free(*ptrs);
		*ptrs = NULL;
		return (1);
	}
	return (0);
}
