#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptrs: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptrs)
{
	if (ptrs && *ptrs)
	{
		free(*ptrs);
		*ptrs = NULL;
		return (1);
	}
	return (0);
}
