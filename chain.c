#include "shell.h"

/**
 * chain_delim - test if current char in buffer is a chain delimeter
 * @details: the parameter struct
 * @buff: the char buffer
 * @m: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_delim(details_t *details, char *buff, size_t *m)
{
	size_t h = *m;

	if (buff[h] == '|' && buff[h + 1] == '|')
	{
		buff[h] = 0;
		h++;
		details->cmd_buf_type = CMD_OR;
	}
	else if (buff[h] == '&' && buff[h + 1] == '&')
	{
		buff[h] = 0;
		h++;
		details->cmd_buf_type = CMD_AND;
	}
	else if (buff[h] == ';') /* found end of this command */
	{
		buff[h] = 0; /* replace semicolon with null */
		details->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*m = h;
	return (1);
}

/**
 * checking_chain - checks if we should continue chaining based on last status
 * @d: the parameter struct
 * @buff: the char buffer
 * @m: address of current position in buf
 * @l: starting position in buff
 * @leng: length of buff
 *
 * Return: Void
 */
void checking_chain(details_t *d, char *buff, size_t *m, size_t l, size_t leng)
{
	size_t h = *m;

	if (d->cmd_buf_type == CMD_AND)
	{
		if (d->status)
		{
			buff[l] = 0;
			h = leng;
		}
	}
	if (d->cmd_buf_type == CMD_OR)
	{
		if (!d->status)
		{
			buff[l] = 0;
			h = leng;
		}
	}

	*m = h;
}

/**
 * replacing_alias - replaces an aliases in the tokenized string
 * @details: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacing_alias(details_t *details)
{
	int q;
	list_t *node;
	char *f;

	for (q = 0; q < 10; q++)
	{
		node = find_node_start(details->alias, details->argv[0], '=');
		if (!node)
			return (0);
		free(details->argv[0]);
		f = _strchr(node->str, '=');
		if (!f)
			return (0);
		f = _strdup(f + 1);
		if (!f)
			return (0);
		details->argv[0] = f;
	}
	return (1);
}

/**
 * replacing_vars - replaces vars in the tokenized string
 * @details: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacing_vars(details_t *details)
{
	int k = 0;
	list_t *node;

	for (k = 0; details->argv[k]; k++)
	{
		if (details->argv[k][0] != '$' || !details->argv[k][1])
			continue;

		if (!_strcmp(details->argv[k], "$?"))
		{
			replacing_string(&(details->argv[k]),
				_strdup(convert_num(details->status, 10, 0)));
			continue;
		}
		if (!_strcmp(details->argv[k], "$$"))
		{
			replacing_string(&(details->argv[k]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = find_node_start(details->env, &details->argv[k][1], '=');
		if (node)
		{
			replacing_string(&(details->argv[k]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replacing_string(&details->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replacing_string - replaces string
 * @oldaddr: address of old string
 * @newstr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacing_string(char **oldaddr, char *newstr)
{
	free(*oldaddr);
	*oldaddr = newstr;
	return (1);
}
