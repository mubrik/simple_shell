#include "./utils/utils.h"

/**
 * _strocr - counts the amount of time a charcter occurs in a str, skips reocr
 * @str_ptr: Src ptr
 * @c: character to locate
 * Return: pointer if located, NULL else
 */
int _strocr(const char *str_ptr, char c)
{
	unsigned int count = 0, i;

	if (!str_ptr || !c)
		return (count);

	for (i = 0; str_ptr[i]; i++)
	{
		if (str_ptr[i] == c && (i && str_ptr[i - 1] != c))
			count++;
	}
	return (count);
}

/**
  * _strcmp - function that compares two strings.
	* @s1_ptr: src 1 pointer char
	* @s2_ptr: src 2 pointer char
	* Return: 0 if equal -1 if s1 less than s2
	* +1 if greater
	*/
int _strcmp(const char *s1_ptr, const char *s2_ptr)
{
	int s1_len, s2_len, iter, max_iter, compare_res;

	/* get len of both */
	s1_len = _strlen(s1_ptr);
	s2_len = _strlen(s2_ptr);
	compare_res = 0;

	/* iterate using longer len*/
	max_iter = s1_len >= s2_len ? s1_len : s2_len;
	iter = 0;

	while (iter < max_iter)
	{
		/* compare val of pointers*/
		compare_res = s1_ptr[iter] - s2_ptr[iter];
		/* if not equal break */
		if (compare_res != 0)
			break;
		iter++;
	}

	return (compare_res);

}

/**
 * _strchr - locates a character in a string.
 * @str_ptr: Src ptr
 * @c: character to locate
 * Return: pointer if located, NULL else
 */
char *_strchr(char *str_ptr, char c)
{
	int i = 0;

	/* cover base case, null byte */
	if (!str_ptr)
		return (NULL);

	/* simple iteration */
	while (str_ptr[i])
	{
		if (str_ptr[i] == c)
			return (&str_ptr[i]);
		i++;
	}

	return (NULL);
}

/**
 * _strtok - tokenize a string using a delim
 * @str: Src ptr
 * @delim: character to locate
 * Return: pointer if located, NULL else
 * Description: custom of builtin strtok, same requirements, buffer then NULL
 */
char *_strtok(char *str, char *delim)
{
	int i, first_f = 0;
	static char *p_stor;
	char *src_ptr = str, *ret_p = NULL, *str_chk;

	if (!str)
		src_ptr = p_stor;
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
				p_stor = &src_ptr[i + 1];
			else
				p_stor = NULL;
			return (ret_p);
		}
	}

	if (!src_ptr[i])
		p_stor = NULL;

	return (ret_p);
}

/**
 * _atoi - function that converts a string to an integer
 * @s: string in question
 * Return: integer
 */
int _atoi(char *s)
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
