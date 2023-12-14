#include "shell.h"

/**
 * _ourhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _ourhistory(details_t *details)
{
	print_list(details->history);
	return (0);
}

/**
 * unsetting_alias - sets alias to string
 * @details: parameter struct
 * @strr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetting_alias(details_t *details, char *strr)
{
	char *q, d;
	int rett;

	q = _strchr(strr, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	rett = delete_node_at_index(&(details->alias),
		get_node_index(details->alias, find_node_start(details->alias, strr, -1)));
	*q = d;
	return (rett);
}

/**
 * setting_alias - sets alias to string
 * @details: parameter struct
 * @strr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setting_alias(details_t *details, char *strr)
{
	char *r;

	r = _strchr(strr, '=');
	if (!r)
		return (1);
	if (!*++r)
		return (unsetting_alias(details, strr));

	unsetting_alias(details, strr);
	return (add_node_end(&(details->alias), strr, 0) == NULL);
}

/**
 * printing_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printing_alias(list_t *node)
{
	char *v = NULL, *g = NULL;

	if (node)
	{
		v = _strchr(node->str, '=');
		for (g = node->str; g <= v; g++)
			_putchar(*g);
		_putchar('\'');
		_puts(v + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ouralias - mimics the alias builtin (man alias)
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ouralias(details_t *details)
{
	int u = 0;
	char *r = NULL;
	list_t *node = NULL;

	if (details->argc == 1)
	{
		node = details->alias;
		while (node)
		{
			printing_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (u = 1; details->argv[u]; u++)
	{
		r = _strchr(details->argv[u], '=');
		if (r)
			setting_alias(details, details->argv[u]);
		else
			printing_alias(find_node_starts_with(details->alias, details->argv[u], '='));
	}

	return (0);
}
