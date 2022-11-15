#include "printf.h"

/**
 * _add_non_printable_chars - do some custom non pr stuff
 * @src_ptr: the char
 * @buffer: the ptr to a buffer
 * @buf_i: index of buffer
 * Description: fragile function, created with sleepy eyes
 * Return: 1 if true, 0 else
 */
int _add_non_printable_chars(char src_ptr, char *buffer, int *buf_i)
{
	int count = 0, character;

	char *hexa = malloc(sizeof(char) * 3);
	/* check */
	if (!hexa)
		return (0);
	/* casting */
	character = (int) src_ptr;
	/* lazy, manually adding \x, \x=single char move count once */
	add_to_buffer('\\', buffer, buf_i);
	add_to_buffer('x', buffer, buf_i), count++;
	/* now get hexa of char to hexa buff */
	int_to_hex_buff(character, hexa, 1);
	/* print hexa */
	capitalize_alpha(&hexa[0]), capitalize_alpha(&hexa[1]);
	add_to_buffer(hexa[0], buffer, buf_i), count++;
	add_to_buffer(hexa[1], buffer, buf_i), count++;
	/* be free little memory */
	free(hexa);

	return (count);
}

/**
 * handle_str_format - adds a string of char to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: number of characters added
 */
int handle_str_format(va_list arg_list, char *buffer,
	int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	char *string_ptr;
	char *null_str = "(null)"; /* print this if NULL */
	int count = 0;

	/* get argument from list */
	string_ptr = va_arg(arg_list, char *);
	/* null check */
	if (!string_ptr)
	{
		while (null_str[count])
		{
			add_to_buffer(null_str[count], buffer, buffer_i), count++;
		}
		return (count);
	}

	while (string_ptr[count])
		add_to_buffer(string_ptr[count], buffer, buffer_i), count++;

	return (count);
}

/**
 * handle_cstr_format - adds a custom string of char to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: number of characters added
 */
int handle_cstr_format(va_list arg_list, char *buffer,
	int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	char *string_ptr;
	char *null_str = "(null)"; /* print this if NULL */
	int count = 0, sub_count = 0;

	/* get argument from list */
	string_ptr = va_arg(arg_list, char *);
	/* null check */
	if (!string_ptr)
	{
		while (null_str[count])
		{
			add_to_buffer(null_str[count], buffer, buffer_i), count++;
		}
		return (count);
	}

	while (string_ptr[count])
	{
		if (is_non_printable(&string_ptr[count]))
		{
			sub_count += _add_non_printable_chars(string_ptr[count], buffer, buffer_i);
			count++;
			continue;
		}
		add_to_buffer(string_ptr[count], buffer, buffer_i), count++;
	}

	return (count + sub_count);
}
