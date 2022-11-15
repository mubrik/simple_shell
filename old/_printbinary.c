#include "printf.h"
/**
 * _int_to_bin_buff - adds binary chars to the buffer
 * @integer: integer
 * @bin_b: the ptr to a buffer
 * @num: num of bytes in buff
 */
void _int_to_bin_buff(unsigned int integer, char *bin_b, int num)
{
	int i;
	/* binary stuff */
	for (i = 0; i < num; i++)
		bin_b[i] = (integer & 1 << (num - i - 1)) ? '1' : '0';
	/* null byte */
	bin_b[num] = '\0';
}

/**
 * handle_bin_format - adds a binary to the buffer
 * @arg_list: args list
 * @buffer: the ptr to a buffer
 * @buffer_i: ptr to index of buffer
 * @mods: ptr of modifiers
 * Return: count of chars added
 */
int handle_bin_format(va_list arg_list, char *buffer,
	int *buffer_i, __attribute__((unused)) Modifiers_t *mods)
{
	unsigned int num, count = 0, bytes;
	char *bin_buffer, *cp_buff;
	/* get num from list */
	num = va_arg(arg_list, int);
	/* base check */
	if (!num)
	{
		add_to_buffer('0', buffer, buffer_i);
		return (1);
	}
	bytes = 32;
	/* maloc */
	bin_buffer = malloc((sizeof(char) * bytes) + 1);
	if (!bin_buffer)
		return (0);
	_int_to_bin_buff(num, bin_buffer, bytes);
	/* push buffer ptr until we hit the fisrt 1 */
	cp_buff = bin_buffer;
	while (*bin_buffer == '0')
		bin_buffer++;
	/* buffer, strat from 1 excluding first zeros of binary */
	while (bin_buffer[count])
	{
		add_to_buffer((bin_buffer[count]), buffer, buffer_i);
		count++;
	}
	/* free buffer */
	free(cp_buff);
	return (count);
}
