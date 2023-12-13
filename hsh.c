#include "shell.h"

/**
 * msl - main shell loop
 * @details: the parameter & return info struct
 * @argvec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int msl(details_t *details, char **argvec)
{
	ssize_t w = 0;
	int builtin_ret = 0;

	while (w != -1 && builtin_ret != -2)
	{
		clearing_info(details);
		if (interactive(details))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		w = get_input(details);
		if (w != -1)
		{
			setting_info(details, argvec);
			builtin_ret = finding_builtin(details);
			if (builtin_ret == -1)
				finding_cmd(details);
		}
		else if (interactive(details))
			_putchar('\n');
		freeing_info(details, 0);
	}
	writing_history(details);
	freeing_info(details, 1);
	if (!interactive(details) && details->status)
		exit(details->status);
	if (builtin_ret == -2)
	{
		if (details->err_num == -1)
			exit(details->status);
		exit(details->err_num);
	}
	return (builtin_ret);
}

/**
 * finding_builtin - finds a builtin command
 * @details: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int finding_builtin(details_t *details)
{
	int k, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _ourexit},
		{"env", _ourenv},
		{"help", _ourhelp},
		{"history", _ourhistory},
		{"setenv", _oursetenv},
		{"unsetenv", _ourunsetenv},
		{"cd", _ourcd},
		{"alias", _ouralias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(details->argv[0], builtintbl[k].type) == 0)
		{
			details->line_count++;
			built_in_ret = builtintbl[k].func(details);
			break;
		}
	return (built_in_ret);
}

/**
 * finding_cmd - finds a command in PATH
 * @details: the parameter & return info struct
 *
 * Return: void
 */
void finding_cmd(details_t *details)
{
	char *path = NULL;
	int o, g;

	details->path = details->argv[0];
	if (details->linecount_flag == 1)
	{
		details->line_count++;
		details->linecount_flag = 0;
	}
	for (o = 0, g = 0; details->arg[o]; o++)
		if (!is_delim(details->arg[o], " \t\n"))
			g++;
	if (!g)
		return;

	path = find_path(details, _getenv(details, "PATH="), details->argv[0]);
	if (path)
	{
		details->path = path;
		forking_cmd(details);
	}
	else
	{
		if ((interactive(details) || _getenv(details, "PATH=")
			|| details->argv[0][0] == '/') && is_commmand(details, details->argv[0]))
			fork_cmd(info);
		else if (*(details->arg) != '\n')
		{
			details->status = 127;
			print_error(details, "not found\n");
		}
	}
}

/**
 * forking_cmd - forks a an exec thread to run cmd
 * @details: the parameter & return info struct
 *
 * Return: void
 */
void forking_cmd(details_t *details)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(details->path, details->argv, get_environ(details)) == -1)
		{
			free_info(details, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(details->status));
		if (WIFEXITED(details->status))
		{
			details->status = WEXITSTATUS(details->status);
			if (details->status == 126)
				print_error(details, "Permission denied\n");
		}
	}
}
