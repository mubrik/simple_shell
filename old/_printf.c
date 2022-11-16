#include "printf.h"

/**
 * _printf - does printf stuff
 * @format: stirng format of string
 * Return: number of bytes printed or -1 for fail
 */
int _printf(const char *format, ...)
{
	int count = 0, index = 0, is_form_spec, *buffer_i = NULL;
	char *pr_buff = NULL, *form_spec_buff = NULL;
	Modifiers_t *pr_mods = NULL;
	Format_handler *format_handler;
	va_list arg_list;
	/* base check */
	if (format == NULL)
		return (-1);
	if (allocate_buff_mem(&pr_buff, &buffer_i, &form_spec_buff, &pr_mods))
		return (-1); /* allocate buffer memory */
	va_start(arg_list, format); /* init varaidic args */
	/* main loop */
	for (index = 0; format[index]; index++)
	{
		is_form_spec = is_format_spec(&format[index], form_spec_buff, pr_mods);
		if (is_form_spec < 0)
		{/* if an error, break loop and print buffer */
			count = is_form_spec;
			break;
		}
		else if (is_form_spec > 0)
		{
			format_handler = get_format_handler(form_spec_buff); /* get handler */
			count += format_handler(arg_list, pr_buff, buffer_i, pr_mods);
			reset_mods(pr_mods), index += is_form_spec;/* reset flags */
		}
		else if (is_form_spec == 0 && is_mods_set(pr_mods))
		{
			index += print_invalid_format_s(format, pr_buff, buffer_i, pr_mods, &count);
			reset_mods(pr_mods);
		}
		else
			add_to_buffer(format[index], pr_buff, buffer_i), count++;
	}
	print_buffer(pr_buff, *buffer_i), va_end(arg_list);
	free_buff_mem(6, pr_buff, pr_mods->flags, pr_mods->length,
		form_spec_buff, buffer_i, pr_mods);
	return (count);
}

/**
	* _perror - variadic wrapper around perror
	* @count: count of args
	* Return: int
	*/
int _perror(unsigned int count, ...)
{
	unsigned int i;
	char *arg = NULL;
	va_list list;
	/* init */
	va_start(list, count);
	/* iterate */
	for (i = 0; i < count; i++)
	{
		/* get arg */
		arg = va_arg(list, char *);
		if (!arg)
			break;
		perror(arg);
	}

	va_end(list);
	return (0);
}
