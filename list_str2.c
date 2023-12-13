/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        h = h->next;
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
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t i = list_len(h), j;
	char **strs;
	char *str;

	if (!h || !i)
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
size_t print_list(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(convert_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
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
