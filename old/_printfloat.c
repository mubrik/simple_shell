#include "printf.h"

/**
 * handle_float_format - add float bytes to a buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: ptr to index of buffer
 * @mods: ptr of modifiers
 * Return: number of bytes added
 */
int handle_float_format(va_list arg_list, char *buffer,
	int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	/* float is promoted to double using va_arg */
	double src_float, dec_part;
	long int int_part, count = 0;

	/* get argument from list */
	src_float = va_arg(arg_list, double);
	/* if neg */
	if (src_float < 0)
	{
		add_to_buffer('-', buffer, buffer_i), count++;
		src_float *= -1; /* make absolute */
	}
	/* split the float to an int by casting it to int */
	int_part = (long int) src_float;
	/* print integer part */
	count += add_int_buff(int_part, buffer, buffer_i);
	/* print dot, increment count */
	add_to_buffer('.', buffer, buffer_i), count++;
	/* get difference from float */
	/* integer will be promoted to double for minus op */
	dec_part = src_float - int_part;
	/* multiply by large number and just print as int */
	dec_part *= 1000000;
	count += add_int_buff((long int) (dec_part + 0.5), buffer, buffer_i);

	return (count);
}

/**
 * int_to_hex_buff - adds hex chars to the buffer
 * @integer: integer
 * @bin_b: the ptr to a buffer
 * @num: num of bytes in buff
 */
void int_to_hex_buff(unsigned int integer, char *bin_b, int num)
{
	int res;

	for (; num >= 0; num--)
	{
		if (integer <= 0)
		{
			bin_b[num] = '0';
			continue;
		}
		res = (integer % 16);
		res = (res > 9) ? (res + 'W') : (res + '0');
		bin_b[num] = res;
		integer /= 16;
	}
}

/*
*Description: abstract
*Consider the number 123.456. Cast it to int (discarding the fraction):
*123. That's an integer, you know how to print it.
*Now subtract 123.456 - 123 = 0.456. That's the fraction you have to print.
*Multiply it by 10: 4.56. Cast it to int: 4.
*That's the first digit after the decimal you have to print.
*Now subtract 4.56 - 4 = 0.56. Multiply it by 10: 5.6.
*Cast it to int to get the next digit past the decimal to print.
*Repeat until the subtraction gives too small a number.
*(Note that it will almost never go to 0.)
*/
