#include "utils.h"

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
