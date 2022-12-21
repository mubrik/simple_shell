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

/**
 * _itoa - int to str
 * @value: number
 * @result: ptr to char
 * @base: number base
 * Return: ptr to char
 * Description: C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char *_itoa(int value, char *result, int base)
{
	char *ptr = NULL, *ptr1 = NULL, tmp_char;
	int tmp_value;
	/* check that the base if valid */
	ptr = result, ptr1 = result;
	if (base < 2 || base > 36)
	{
		*result = '\0';
		return (result);
	}

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghi\
		jklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
	} while (value);

	/* Apply negative sign */
	if (tmp_value < 0)
		*ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr)
	{
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return (result);
}

/**
 * _str_comment - strips the comment from a string
 * @shell_d: shell data
 * Return: int, len.
 */
int _str_comment(shell_data_t *shell_d)
{
	int is_quote = 0, count = 0;
	buf tmp;

	if (!shell_d)
		return (count);
	tmp = shell_d->input_buff;

	for (count = 0; tmp[count]; count++)
	{
		if (tmp[count] == '"')
			is_quote = is_quote ? 0 : 1;

		if (tmp[count] == '#' && !is_quote &&
			(tmp[count - 1] == '\0' || tmp[count - 1] == ' '))
			tmp[count] = '\0';
	}

	return (count);
}
