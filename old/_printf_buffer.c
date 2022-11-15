#include "printf.h"

/**
 * print_buffer - writes bytes of a buffer to stdout
 * @buffer: the ptr to a buffer
 * @byte_count: number of byte to write
 * Return: the next available index int
 */
int print_buffer(char *buffer, int byte_count)
{
	return (write(1, buffer, byte_count));
}

/**
 * add_to_buffer - adds a charatcter to index of a buffer
 * @str: the character
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * Return: the next available index int
 */
int add_to_buffer(char str, char *buffer, int *buffer_i)
{
	if (*buffer_i >= PRINT_BUFF_SIZE)
	{
		/* flush/print out the buffer */
		print_buffer(buffer, PRINT_BUFF_SIZE);
		/* set index to start */
		*buffer_i = 0;
	}
	/* add chr to buffer and incr index */
	buffer[*buffer_i] = str,
	*buffer_i += 1;
	return (*buffer_i);
}

/**
 * allocate_buff_mem - reducing lines in main func,
 * moving malloc and check here
 * @pr_buff: ptr to ptr of main print buffer
 * @pr_buff_index: ptr to ptr of INDEX of print buffer
 * @format_spec_buff: ptr to ptr of format specification buffer
 * @mods: ptr to ptr of modifiers
 * Return: 0 on success, 1 on failure
 */
int allocate_buff_mem(char **pr_buff, int **pr_buff_index,
	char **format_spec_buff, Modifiers_t **mods)
{
	Format_flag_t *format_flags;
	Length_mod_t *length_mods;
	/* allocate buffer space */
	*pr_buff = malloc(sizeof(char) * PRINT_BUFF_SIZE);
	*pr_buff_index = malloc(sizeof(int));
	*format_spec_buff = malloc(sizeof(char) + 1);
	*mods = malloc(sizeof(Modifiers_t));
	format_flags = malloc(sizeof(Format_flag_t));
	length_mods = malloc(sizeof(Length_mod_t));
	/* check */
	if (!(*format_spec_buff) || !(*pr_buff) || (!(*mods)) ||
		(!format_flags) || !(*pr_buff_index) || (!length_mods))
	{
		return (1);
	}
	/* set flags/attribs, not necessary but best be explicit i guess */
	format_flags->minus = 0, format_flags->zero = 0, format_flags->plus = 0;
	format_flags->space = 0, length_mods->long_m = 0, length_mods->short_m = 0;
	format_flags->pound = 0, (*mods)->flags = format_flags;
	(*mods)->length = length_mods, (*mods)->precision = 0, (*mods)->width = 0;
	**pr_buff_index = 0;

	return (0);
}

/**
 * free_buff_mem - frees up buffer in args
 * @num: num of args
 * Return: 0 on success, 1 on failure
 */
int free_buff_mem(int num, ...)
{
	int index;
	va_list arg_list;

	if (num <= 0)
		return (1);
	/* init variadic */
	va_start(arg_list, num);
	/* iterate and free pointers */
	for (index = 0; index < num; index++)
	{
		free(va_arg(arg_list, char *)); /* be free arguments */
	}
	va_end(arg_list);
	return (0);
}

/**
 * reset_mods - resets modifiers to default
 * @mods: ptr to ptr of modifiers
 * Return: 0 on success, 1 on failure
 */
int reset_mods(Modifiers_t *mods)
{
	/* set flags/attribs, not necessary but best be explicit i guess */
	mods->flags->minus = 0, mods->flags->zero = 0, mods->flags->plus = 0;
	mods->flags->space = 0, mods->length->long_m = 0, mods->length->short_m = 0;
	mods->flags->pound = 0, mods->precision = 0, mods->width = 0;

	return (0);
}
