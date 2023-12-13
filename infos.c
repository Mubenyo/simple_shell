#include "shell.h"

/**
 * clearing_info - initializes info_t struct
 * @details: struct address
 */
void clearing_info(details_t *details)
{
	details->arg = NULL;
	details->argv = NULL;
	details->path = NULL;
	details->argc = 0;
}

/**
 * setting_info - initializes info_t struct
 * @details: struct address
 * @argvec: argument vector
 */
void setting_info(details_t *details, char **argvec)
{
	int f = 0;

	details->fname = argvec[0];
	if (details->arg)
	{
		details->argv = strtowords(details->arg, " \t");
		if (!details->argv)
		{

			details->argv = malloc(sizeof(char *) * 2);
			if (details->argv)
			{
				details->argv[0] = _strdup(details->arg);
				details->argv[1] = NULL;
			}
		}
		for (f = 0; details->argv && details->argv[f]; f++)
			;
		details->argc = f;

		replace_alias(details);
		replace_vars(details);
	}
}

/**
 * freeing_info - frees info_t struct fields
 * @details: struct address
 * @alls: true if freeing all fields
 */
void freeing_info(details_t *details, int alls)
{
	ffree(details->argv);
	details->argv = NULL;
	details->path = NULL;
	if (alls)
	{
		if (!details->cmd_buf)
			free(details->arg);
		if (details->env)
			free_list(&(details->env));
		if (details->history)
			free_list(&(details->history));
		if (details->alias)
			free_list(&(details->alias));
		ffree(details->environ);
			details->environ = NULL;
		freeAndNull((void **)details->cmd_buf);
		if (details->readfd > 2)
			close(details->readfd);
		_putchar(BUF_FLUSH);
	}
}
