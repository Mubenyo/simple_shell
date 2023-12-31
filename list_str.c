#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @listHead: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **listHead, const char *str, int num)
{
	list_t *newNode;

	if (!listHead)
		return (NULL);

	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	newNode->next = *listHead;
	*listHead = newNode;
	return (newNode);
}


/**
 * add_node_end - adds a node to the end of the list
 * @listHead: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **listHead, const char *str, int num)
{
	list_t *new_node, *node;

	if (!listHead)
		return (NULL);

	node = *listHead;
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
		*listHead = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a str_list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * delete_node_at_index - deletes node at given index
 * @listHead: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **listHead, unsigned int index)
{
	list_t *current, *previous;
	unsigned int i = 0;

	if (!listHead || !*listHead)
		return (0);

	if (!index)
	{
		current = *listHead;
		*listHead = (*listHead)->next;
		free(current->str);
		free(current);
		return (1);
	}
	current = *listHead;
	while (current)
	{
		if (i == index)
		{
			previous->next = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		i++;
		previous = current;
		current = current->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;

}
