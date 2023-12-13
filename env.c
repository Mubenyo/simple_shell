#include "shell.h"

/**
 * _ourenv - prints the current environment
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _ourenv(details_t *details)
{
	print_list_str(details->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @details: Structure containing potential arguments. Used to maintain
 * @envname: env var name
 *
 * Return: the value
 */
char *_getenv(details_t *details, const char *envname)
{
	list_t *node = details->env;
	char *v;

	while (node)
	{
		v = starts_with(node->str, envname);
		if (v && *v)
			return (v);
		node = node->next;
	}
	return (NULL);
}

/**
 * _oursetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _oursetenv(details_t *details)
{
	if (details->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setsenv(details, details->argv[1], details->argv[2]))
		return (0);
	return (1);
}

/**
 * _ourunsetenv - Remove an environment variable
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _ourunsetenv(details_t *details)
{
	int j;

	if (details->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= details->argc; j++)
		unsetenv(details, details->argv[j]);

	return (0);
}

/**
 * increase_env_list - increases env linked list
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int increase_env_list(details_t *details)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	details->env = node;
	return (0);
}
