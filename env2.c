#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(details_t *details)
{
	if (!details->environ || details->env_changed)
	{
		details->environ = list_to_strings(details->env);
		details->env_changed = 0;
	}

	return (details->environ);
}

/**
 * _envunset - Remove an environment variable
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @strvar: the string env var property
 */
int _envunset(details_t *details, char *strvar)
{
	list_t *node = details->env;
	size_t n = 0;
	char *d;

	if (!node || !strvar)
		return (0);

	while (node)
	{
		d = starts_with(node->str, strvar);
		if (d && *d == '=')
		{
			details->env_changed = delete_node_at_index(&(details->env), n);
			n = 0;
			node = details->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (details->env_changed);
}

/**
 * _setsenv - Initialize a new environment variable,
 *             or modify an existing one
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @strvar: the string env var property
 * @strvalue: the string env var value
 *  Return: Always 0
 */
int _setsenv(details_t *details, char *strvar, char *strvalue)
{
	char *buff = NULL;
	list_t *node;
	char *d;

	if (!strvar || !strvalue)
		return (0);

	buff = malloc(_strlen(strvar) + _strlen(strvalue) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, strvar);
	_strcat(buff, "=");
	_strcat(buff, strvalue);
	node = details->env;
	while (node)
	{
		d = starts_with(node->str, strvar);
		if (d && *d == '=')
		{
			free(node->str);
			node->str = buff;
			details->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(details->env), buff, 0);
	free(buff);
	details->env_changed = 1;
	return (0);
}
