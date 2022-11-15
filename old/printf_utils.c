#include "printf.h"

/**
 * capitalize_alpha - capitalize an alphabet char
 * @src_ptr: the ptr to char character
 * Return: void
 */
void capitalize_alpha(char *src_ptr)
{
	if (!src_ptr)
		return;

	if (*src_ptr >= 'a' && *src_ptr <= 'z')
		*src_ptr = *src_ptr - 32;
}

/**
 * is_non_printable - check if non printable
 * @src_ptr: ptr to char
 * Return: 1 if true, 0 else
 */
int is_non_printable(char *src_ptr)
{
	if (!src_ptr)
		return (0);
	if (*src_ptr < ' ' || *src_ptr >= 127)
		return (1);
	return (0);
}

/**
 * atoi_m - function that converts a string to an integer
 * @s: string in question
 * Return: integer
 */
int atoi_m(char *s)
{
	int i, num, neg;

	neg = 1;
	i = num = 0;
	while ((s[i] < '0' || s[i] > '9') && s[i] != 0)
	{
		if (s[i] == '-')
			neg = neg * -1;
		i++;
	}
	while ((s[i] >= '0' && s[i] <= '9') && s[i] != 0)
	{
		if (num >= 0)
		{
			num = num * 10 - (s[i] - '0');
			i++;
		}
		else
		{
			num = num * 10 - (s[i] - '0');
			i++;
		}
	}
	neg = neg * -1;
	return (num * neg);
}

/**
 * p_by - counts the amount of time a specific char is repeated and return
 * @src_ptr: src char ptr
 * @c: the char
 * @index: index to start
 * Return: count
 */
int p_by(const char *src_ptr, char c, int index)
{
	int count = 0;

	/* get amt of space to push by */
	while (is_flag_character(src_ptr[index]))
	{
		if (src_ptr[index] == c)
			count++;
		index++;
	}

	return (count);
}

/**
 * init_spec_chk - checks len modify
 * @str: ptr to strin
 * Return: int
 */
int init_spec_chk(const char *str)
{
	if (str[0] != '%')
		return (0);
	if (str[1] == '\0')
		return (-1);
	return (1);
}
