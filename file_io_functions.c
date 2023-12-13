#include "shell.h"

/**
 * getting_history_file - gets the history file
 * @details: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getting_history_file(details_t *details)
{
	char *buff, *dirr;

	dir = _getenv(details, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * writing_history - creates a file, appends to an existing file
 * @details: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writing_history(details_t *details)
{
	ssize_t fdescrip;
	char *filename = getting_history_file(details);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdescrip = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdescrip == -1)
		return (-1);
	for (node = details->history; node; node = node->next)
	{
		_putsfd(node->str, fdescrip);
		_putfd('\n', fdescrip);
	}
	_putfdescrip(BUF_FLUSH, fdescrip);
	close(fdescrip);
	return (1);
}

/**
 * reading_history - reads history from file
 * @details: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int reading_history(details_t *details)
{
	int f, last = 0, linecount = 0;
	ssize_t fdescrip, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = getting_history_file(details);

	if (!filename)
		return (0);

	fdescrip = open(filename, O_RDONLY);
	free(filename);
	if (fdescrip == -1)
		return (0);
	if (!fstat(fdescrip, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdescrip, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fdescrip);
	for (f = 0; f < fsize; f++)
		if (buff[f] == '\n')
		{
			buff[f] = 0;
			build_history_list(details, buff + last, linecount++);
			last = f + 1;
		}
	if (last != f)
		build_history_list(details, buff + last, linecount++);
	free(buff);
	details->histcount = linecount;
	while (details->histcount-- >= HIST_MAX)
		delete_node_at_index(&(details->history), 0);
	renumber_history(details);
	return (details->histcount);
}

/**
 * building_history_list - adds entry to a history linked list
 * @details: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int building_history_list(details_t *details, char *buff, int linecount)
{
	list_t *node = NULL;

	if (details->history)
		node = details->history;
	add_node_end(&node, buff, linecount);

	if (!details->history)
		details->history = node;
	return (0);
}

/**
 * renumbering_history - renumbers the history linked list after changes
 * @details: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumbering_history(details_t *details)
{
	list_t *node = details->history;
	int v = 0;

	while (node)
	{
		node->num = v++;
		node = node->next;
	}
	return (details->histcount = v);
}
