#include "./utils/utils.h"

/**
	* _strcpy - copies the string pointed to by src,
	* including the terminating null byte (\0), to the buffer pointed to by dest
	* @dest: buffer ptr
	* @src: buffer ptr
	* Return: void
	*/
char *_strcpy(char *dest, char *src)
{
	char *first;

	/* copy first pointer */
	first = dest;

	/* iterate, end after hitting null byte */
	while (*src != '\0')
		*dest = *src, src++, dest++;

	/* add null pointer to last */
	*dest = '\0';

	return (first);
}


/**
	* _strlen - returns the length of a string.
	* @src_ptr: str buffer
	* Return: int length
	*/
int _strlen(const char *src_ptr)
{
	/* implement null checking? orignal doesnt seem to? */
	/* checking if the current value of pointer not null */
	if (*src_ptr != 0)
	{
		/* move the pointer foward and call the function again adding 1! */
		src_ptr++;
		return (1 + _strlen(src_ptr));
	}

	return (0);
}

/**
	* _strconcat - concats two string, malloc'd
	* @src: str buffer
	* @add_str: str buffer
	* Return: ptr to malloc'd string
	*/
char *_strconcat(const char *src, const char *add_str)
{
	unsigned int len1, len2;

	char *new = malloc((len1 = _strlen(src)) + (len2 = _strlen(add_str)) + 1);

	if (new)
		_memcpy(src, new), _memcpy(add_str, &new[len1]), new[len1 + len2] = '\0';
	return (new);
}

/**
	* _strconcatv - concats multiple strings, malloc'd, variadic
	* @src: str buffer
	* @count: count of args
	* Return: ptr to malloc'd string
	*/
char *_strconcatv(const char *src, unsigned int count, ...)
{
	unsigned int i;
	char *prev = NULL, *next = NULL, *arg = NULL;
	va_list list;
	/* check */
	if (!src)
		return (NULL);
	/* copy  */
	prev = _strdup(src);
	/* init */
	va_start(list, count);
	/* iterate */
	for (i = 0; i < count; i++)
	{
		/* get arg */
		arg = va_arg(list, char *);
		if (!arg)
			break;
		/* concat arg with prev strig */
		next = _strconcat(prev, arg); /* malloc'd */
		if (!next)
			return (NULL); /* check */
		if (prev)
			free(prev); /* free prev malloc'd string */
		prev = next; /* copy new ptr to prev */
	}

	va_end(list);
	return (next);
}

/**
	* _strdup - copies the string pointed to by src,
	* including the terminating null byte (\0), to a malloc buffer
	* @src: buffer ptr
	* Return: ptr to malloc'd string or null
	*/
char *_strdup(const char *src)
{
	unsigned int len = _strlen(src);

	char *new = malloc(len + 1);

	if (new)
		_memcpy(src, new), new[len] = '\0';
	return (new);
}
