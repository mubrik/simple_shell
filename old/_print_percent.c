#include "printf.h"

/**
 * _long_to_hex_buff - adds hex chars to the buffer
 * @long_num: number of type long
 * @bin_b: the ptr to a buffer
 * @num: num of bytes in buff
 */
void _long_to_hex_buff(unsigned long int long_num, char *bin_b, int num)
{
	int res;

	for (; num >= 0; num--)
	{
		if (long_num <= 0)
		{
			bin_b[num] = '0';
			continue;
		}
		res = (long_num % 16);
		res = (res > 9) ? (res + 'W') : (res + '0');
		bin_b[num] = res;
		long_num /= 16;
	}
}

/**
 * handle_percent_format - adds a % to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: 1
 */
int handle_percent_format(__attribute__((unused)) va_list arg_list,
	char *buffer, int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	/* beffer */
	add_to_buffer('%', buffer, buffer_i);
	return (1);
}

/**
 * handle_pointer_format - adds the address of a variable to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * @mods: ptr of modifiers
 * Return: 1
 */
int handle_pointer_format(__attribute__((unused)) va_list arg_list,
	char *buffer, int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	unsigned long int addr;
	unsigned int bytes, count = 0;
	char *bin_buffer, *cp_buff, *null_str = "(nil)"; /* print this if NULL */
	/* get arg */
	addr = va_arg(arg_list, long);
	/* null check */
	if (!addr)
	{
		while (null_str[count])
		{
			add_to_buffer(null_str[count], buffer, buffer_i), count++;
		}
		return (count);
	}
	bytes = 17; /* max needed for unsigned long long int to hex */
	/* maloc */
	bin_buffer = malloc((sizeof(char) * bytes) + 1);
	if (!bin_buffer)
		return (0);
	bin_buffer[bytes + 1] = '\0';
	_long_to_hex_buff(addr, bin_buffer, bytes);
	/* add prepend 0x to buffer */
	add_to_buffer('0', buffer, buffer_i);
	add_to_buffer('x', buffer, buffer_i);
	/* cp then push buffer ptr until we hit the fisrt non zero*/
	cp_buff = bin_buffer;
	while (*bin_buffer == '0')
		bin_buffer++;
	while (bin_buffer[count])
	{
		add_to_buffer((bin_buffer[count]), buffer, buffer_i);
		count++;
	}
	/* accounting for 0x added before loop */
	count += 2;
	/* free buffer */
	free(cp_buff);
	return (count);
}
