#include "printf.h"

/**
 * add_long_int_buff - add long int number to buffer
 * @num: integer to add
 * @buffer: the ptr to a buffer
 * @buffer_i: ptr index of buffer
 * Return: count of bytes added to buffer
 */
int add_long_int_buff(unsigned long int num, char *buffer, int *buffer_i)
{
	unsigned long int count = 0;
	unsigned long int div_by;

	div_by = 1;
	while ((num / div_by) > 9)
		div_by *= 10;
	while (div_by > 0)
	{
		add_to_buffer(((num / div_by) % 10) + '0', buffer, buffer_i);
		count++, div_by /= 10;
	}

	return (count);
}

/**
 * add_int_buff - add number to buffer
 * @num: integer to add
 * @buffer: the ptr to a buffer
 * @buffer_i: ptr index of buffer
 * Return: count of bytes added to buffer
 */
int add_int_buff(unsigned int num, char *buffer, int *buffer_i)
{
	unsigned int count = 0;
	unsigned int div_by;

	div_by = 1;
	while ((num / div_by) > 9)
		div_by *= 10;
	while (div_by > 0)
	{
		add_to_buffer(((num / div_by) % 10) + '0', buffer, buffer_i);
		count++, div_by /= 10;
	}

	return (count);
}

/**
 * handle_int_format - adds numbers of type long int to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: number of integers added
 */
int handle_int_format(va_list arg_list, char *buffer,
	int *buffer_i, Modifiers_t *mods)
{
	int count = 0, is_neg = 0;
	long int l_number = 0;
	int s_number = 0;

	/* get argument from list, check modifier for long */
	if (mods->length->long_m)
	{
		l_number = va_arg(arg_list, long int);
		if (l_number < 0)
		{
			add_to_buffer('-', buffer, buffer_i), is_neg = 1, count++;
			l_number *= -1; /* make absolute */
		}
	}
	else
	{
		s_number = va_arg(arg_list, int);
		/* neg number */
		if (s_number < 0)
		{
			add_to_buffer('-', buffer, buffer_i), is_neg = 1, count++;
			s_number *= -1; /* make absolute */
		}
	}
	/* handle + flag */
	if ((mods->flags->plus) && !is_neg)
		add_to_buffer('+', buffer, buffer_i), count++;
	/* handle space flag, plus flag takes priority */
	if ((mods->flags->space) && !is_neg && !(mods->flags->plus))
		add_to_buffer(' ', buffer, buffer_i), count++;
	if (mods->length->long_m)
		count += add_long_int_buff(l_number, buffer, buffer_i);
	else
		count += add_int_buff(s_number, buffer, buffer_i);
	return (count);

}

/**
 * handle_uint_format - adds numbers of type unsigned int
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: number of integers added
 * Description: only diff btw this and int is negative check
 */
int handle_uint_format(va_list arg_list, char *buffer,
	int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	unsigned long int l_number = 0, count = 0;
	unsigned int s_number = 0;

	/* get argument from list, check modifier for long */
	if (mods->length->long_m)
	{
		l_number = va_arg(arg_list, long int);
		count += add_long_int_buff(l_number, buffer, buffer_i);
	}
	else
	{
		s_number = va_arg(arg_list, int);
		count += add_int_buff(s_number, buffer, buffer_i);
	}

	return (count);

}
