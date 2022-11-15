#include "printf.h"

/**
 * long_int_to_oct_buff - adds long octal chars to the buffer
 * @integer: integer
 * @bin_b: the ptr to a buffer
 * @num: num of bytes in buff
 */
void long_int_to_oct_buff(unsigned long int integer, char *bin_b, int num)
{

	for (; num >= 0; num--)
	{
		if (integer <= 0)
		{
			bin_b[num] = '0';
			continue;
		}
		bin_b[num] = (integer % 8) + '0';
		integer /= 8;
	}
}

/**
 * long_int_to_hex_buff - adds long hex chars to the buffer
 * @integer: integer
 * @bin_b: the ptr to a buffer
 * @num: num of bytes in buff
 */
void long_int_to_hex_buff(unsigned long int integer, char *bin_b, int num)
{
	long int res;

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

/**
 * long_int_to_oct_buff - adds long octal chars to the buffer
 * @format: ptr to strin
 * @len: len modifier
 * @count: ptr to count
 * @index: index
 */
void handle_mod_lencheck(const char *format, Length_mod_t *len,
	int *count, int index)
{
	if (len->long_m)
	{
		while (format[index])
		{
			if (format[index] == 'l')
				*count += 1;
			index++;
		}
	}

	if (len->short_m)
	{
		while (format[index])
		{
			if (format[index] == 'h')
				*count += 1;
			index++;
		}
	}
}
