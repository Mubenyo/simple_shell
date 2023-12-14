#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @dest: the pointer to the memory area
 * @ch: the byte to fill *dest with
 * @count: the amount of bytes to be filled
 * Return: (dest) a pointer to the memory area dest
 */
char *_memset(char *dest, char ch, unsigned int count)
{
	unsigned int i;
	
	for (i = 0; i < count; i++)
		dest[i] = ch;
	return dest;
}

/**
 * _free - frees a string of strings
 * @str_arr: string of strings
 */
void _free(char **str_arr)
{
	char **temp = str_arr;
	
	if (!str_arr)
        return;
	
	while (*str_arr)
		free(*str_arr++);
	free(temp);
}


/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * freeAndNull - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freeAndNull(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
