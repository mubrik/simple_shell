#include "shell.h"

/**
 * _strtok_r - tokenize a string using a delim
 * @str: Src ptr
 * @delim: character to locate
 * @saveptr: ptr to track sesiion
 * Return: pointer if located, NULL else
 * Description: custom of builtin strtok, same requirements, buffer then NULL
 */
char *_strtok_r(char *str, char *delim, char **saveptr)
{
	int i, first_f = 0;
	char *src_ptr = str, *ret_p = NULL, *str_chk;

	if (!str)
		src_ptr = *saveptr;
	if (!src_ptr)
		return (NULL);
	for (i = 0; src_ptr[i]; i++)
	{
		str_chk = _strchr(delim, src_ptr[i]);
		if (!first_f && !str_chk)
			ret_p = &src_ptr[i], first_f = 1;
		if (first_f && str_chk)
		{
			src_ptr[i] = '\0';
			if (src_ptr[i + 1])
				*saveptr = &src_ptr[i + 1];
			else
				*saveptr = NULL;
			return (ret_p);
		}
	}

	if (!src_ptr[i])
		*saveptr = NULL;

	return (ret_p);
}

/**
  * *_strncpy - function that copies a string.
	* @src_ptr: src pointer char
	* @dest_ptr: destination pointer char
	* @n: number to add
	* Return: *char
	*/
char *_strncpy(char *src_ptr, char *dest_ptr, int n)
{
	int i = 0;

	/* now add dst value from nul ptr */
	while (i < n)
	{
		/* use iteration length to add to pointer */
		dest_ptr[i] = src_ptr[i], i++;
	}

	return (dest_ptr);
}

/**
 * _strspn - gets the length of a prefix substring.
 * @src: the string
 * @accept: characters
 * Return: int, len.
 */
unsigned int _strspn(char *src, char *accept)
{

	if (!accept || !src || *accept == '\0' || *src == '\0')
		return (0);
	/* check if string in accept */
	if (*accept == *src)
	{
		/* string is in, push forward and call again adding 1 */
		src++, accept++;
		return (1 + _strspn(src, accept));
	}
	/* recursive base condition */
	return (0);
}
