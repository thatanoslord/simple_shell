#include "shell.h"

/**
 * *shell_add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *shell_add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * *shell_add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @strs: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *shell_add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * shell_print_list_str - prints only the str element of a list_t linked list
 * @z: pointer to first node
 *
 * Return: size of list
 */
size_t shell_print_list_str(const list_t *z)
{
	size_t i = 0;

	while (z)
	{
		_puts(z->str ? z->str : "(nil)");
		_puts("\n");
		z = z->next;
		i++;
	}
	return (i);
}

/**
 * shell_delete_node_at_index - deletes node at given index
 * @heads: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int shell_delete_node_at_index(list_t **heads, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!heads || !*heads)
		return (0);

	if (!index)
	{
		node = *heads;
		*heads = (*heads)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *heads;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * shell_free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void shell_free_list(list_t **heads_ptr)
{
	list_t *node, *next_node, *heads;

	if (!heads_ptr || !*heads_ptr)
		return;
	heads = *heads_ptr;
	node = heads;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*heads_ptr = NULL;
}
