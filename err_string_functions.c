#include "shell.h"

/**
 *_eputs - prints an input string
 * @strng: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *strng)
{
	int k = 0;

	if (!strng)
		return;
	while (strng[k] != '\0')
	{
		_eputchar(strng[k]);
		k++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @b: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char b)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (b != BUF_FLUSH)
		buff[i++] = b;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @b: The character to print
 * @fdescrip: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char b, int fdescrip)
{
	static int h;
	static char buff[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || h >= WRITE_BUF_SIZE)
	{
		write(fdescrip, buff, h);
		h = 0;
	}
	if (b != BUF_FLUSH)
		buff[h++] = b;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @strng: the string to be printed
 * @fdescrip: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *strng, int fdescrip)
{
	int m = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		m += _putfd(*strng++, fdescrip);
	}
	return (m);
}
