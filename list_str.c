#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @listHead: address of pointer to head node
 * @str: str field of node
 * @index: node index used by history
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
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **listHead, const char *str, int index)
{
	list_t *new_node, *node;

	if (!listHead)
		return (NULL);

	node = *listHead;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
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
 * print_str_list - prints only the str element of a str_list_t linked list
 * @listHead: pointer to first node
 *
 * Return: size of list
 */
size_t print_str_list(const str_list_t *listHead)
{
    size_t count = 0;

    while (listHead)
    {
        _puts(listHead->str ? listHead->str : "(nil)");
        _puts("\n");
        listHead = listHead->next;
        count++;
    }
    return (count);
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


/**
 * list_len - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		index++;
	}
	return (index);
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @current_node: pointer to list head
 * @search_prefix: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *find_node_starts_with(list_t *current_node, char *search_prefix, char next_char)
{
    char *match_ptr = NULL;

    while (current_node)
    {
        match_ptr = starts_with(current_node->str, search_prefix);
        if (match_ptr && ((next_char == -1) || (*match_ptr == next_char)))
            return (current_node);
        current_node = current_node->next;
    }
    return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @list_head: pointer to list head
 * @target_node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *list_head, list_t *target_node)
{
    size_t index = 0;

    while (list_head)
    {
        if (list_head == target_node)
            return (index);
        list_head = list_head->next;
        index++;
    }
    return (-1);
}
