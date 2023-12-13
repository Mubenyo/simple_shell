#include "shell.h"

/**
 * _ourexit - exits our shell
 * @details: Structure containing potential arguments.Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if details.argv[0] != "exit"
 */
int _ourexit(details_t *details)
{
	int exitchecker;

	if (details->argv[1])
	{
		exitchecker = err_str_to_int(details->argv[1]);
		if (exitchecker == -1)
		{
			details->status = 2;
			print_error(details, "Illegal number: ");
			_eputs(details->argv[1]);
			_eputchar('\n');
			return (1);
		}
		details->err_num = err_str_to_int(details->argv[1]);
		return (-2);
	}
	details->err_num = -1;
	return (-2);
}

/**
 * _ourcd - changes the current directory of the process
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ourcd(details_t *details)
{
	char *m, *dirr, buffer[1024];
	int changedir_ret;

	m = getcwd(buffer, 1024);
	if (!m)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!details->argv[1])
	{
		dirr = _getenv(details, "HOME=");
		if (!dirr)
			changedir_ret = /* TODO: what should this be? */
				chdir((dirr = _getenv(details, "PWD=")) ? dirr : "/");
		else
			changedir_ret = chdir(dirr);
	}
	else if (_strcmp(details->argv[1], "-") == 0)
	{
		if (!_getenv(details, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(details, "OLDPWD=")), _putchar('\n');
		changedir_ret = /* TODO: what should this be? */
			chdir((dirr = _getenv(details, "OLDPWD=")) ? dirr : "/");
	}
	else
		changedir_ret = chdir(details->argv[1]);
	if (changedir_ret == -1)
	{
		print_error(details, "can't cd to ");
		_eputs(details->argv[1]), _eputchar('\n');
	}
	else
	{
		_setsenv(details, "OLDPWD", _getenv(details, "PWD="));
		_setsenv(details, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ourhelp - changes the current directory of the process
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ourhelp(details_t *details)
{
	char **argm_array;

	argm_array = details->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argm_array); /* temp att_unused workaround */
	return (0);
}
