#include "printf.h"

/**
 * handle_char_format - adds a single char to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: 1, single character added
 */
int handle_char_format(va_list arg_list, char *buffer,
	int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	int str;
	/* get str from list */
	str = va_arg(arg_list, int);
	/* beffer */
	add_to_buffer(str, buffer, buffer_i);

	return (1);
}
