#include "shell.h"

/**
 * _ourhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _ourhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetting_alias - sets alias to string
 * @info: parameter struct
 * @strr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetting_alias(info_t *info, char *strr)
{
	char *q, d;
	int rett;

	q = _strchr(strr, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	rett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, strr, -1)));
	*q = d;
	return (rett);
}

/**
 * setting_alias - sets alias to string
 * @info: parameter struct
 * @strr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setting_alias(info_t *info, char *strr)
{
	char *r;

	r = _strchr(strr, '=');
	if (!r)
		return (1);
	if (!*++r)
		return (unsetting_alias(info, strr));

	unsetting_alias(info, strr);
	return (add_node_end(&(info->alias), strr, 0) == NULL);
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
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ouralias(info_t *info)
{
	int u = 0;
	char *r = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printing_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (u = 1; info->argv[u]; u++)
	{
		r = _strchr(info->argv[u], '=');
		if (r)
			setting_alias(info, info->argv[u]);
		else
			printing_alias(node_starts_with(info->alias, info->argv[u], '='));
	}

	return (0);
}
