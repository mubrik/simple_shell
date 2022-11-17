#include "utils.h"

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
