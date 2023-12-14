#include "shell.h"

/**
 * inputing_buff - buffers chained commands
 * @details: parameter struct
 * @buff: address of buffer
 * @leng: address of len var
 *
 * Return: bytes read
 */
ssize_t inputing_buff(details_t *details, char **buff, size_t *leng)
{
	ssize_t t = 0;
	size_t leng_p = 0;

	if (!*leng) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)details->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, signintHandler);
#if USE_GETLINE
		t = getline(buff, &leng_p, stdin);
#else
		t = _getline(details, buff, &leng_p);
#endif
		if (t > 0)
		{
			if ((*buff)[t - 1] == '\n')
			{
				(*buff)[t - 1] = '\0'; /* remove trailing newline */
				t--;
			}
			details->linecount_flag = 1;
			rm_comments(*buff);
			building_history_list(details, *buff, details->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*leng = t;
				details->cmd_buf = buff;
			}
		}
	}
	return (t);
}

/**
 * getting_input - gets a line minus the newline
 * @details: parameter struct
 *
 * Return: bytes read
 */
ssize_t getting_input(details_t *details)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t m, n, leng;
	ssize_t v = 0;
	char **buff_d = &(details->arg), *d;

	_putchar(BUF_FLUSH);
	v = inputing_buff(details, &buff, &leng);
	if (v == -1) /* EOF */
		return (-1);
	if (leng)	/* we have commands left in the chain buffer */
	{
		n = m; /* init new iterator to current buff position */
		d = buff + m; /* get pointer for return */

		checking_chain(details, buff, &n, m, leng);
		while (n < leng) /* iterate to semicolon or end */
		{
			if (is_chain(details, buff, &n))
				break;
			n++;
		}

		m = n + 1; /* increment past nulled ';'' */
		if (m >= leng) /* reached end of buffer? */
		{
			m = leng = 0; /* reset position and length */
			details->cmd_buf_type = CMD_NORM;
		}

		*buff_d = d; /* pass back pointer to current command position */
		return (_strlen(d)); /* return length of current command */
	}

	*buff_d = buff; /* else not a chain, pass back buffer from _getline() */
	return (v); /* return length of buffer from _getline() */
}

/**
 * reading_buff - reads a buffer
 * @details: parameter struct
 * @buff: buffer
 * @q: size
 *
 * Return: l
 */
ssize_t reading_buff(details_t *details, char *buff, size_t *q)
{
	ssize_t l = 0;

	if (*q)
		return (0);
	l = read(details->readfd, buff, READ_BUF_SIZE);
	if (l >= 0)
		*q = l;
	return (l);
}

/**
 * _getline - gets the next line of input from STDIN
 * @details: parameter struct
 * @pntr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: u
 */
int _getline(details_t *details, char **pntr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, leng;
	size_t k;
	ssize_t l = 0, u = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pntr;
	if (p && length)
		u = *length;
	if (i == leng)
		i = leng = 0;

	l = reading_buff(details, buff, &leng);
	if (l == -1 || (l == 0 && leng == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : leng;
	new_p = _realloc(p, u, u ? u + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (u)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	u += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = u;
	*pntr = p;
	return (u);
}

/**
 * signintHandler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void signintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
