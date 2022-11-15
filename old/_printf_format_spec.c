#include "printf.h"

/**
 * _is_format_spec_char - checks if char is a format spec char "cdefgiosux%"
 * @c: character
 * Return: 1 if true, 0 else
 */
int _is_format_spec_char(char c)
{
	/* all spec "cdefgiosuxp%" custom: "bSX" */
	char *spec_arr = "cs%";

	/* iterate */
	while (*spec_arr != '\0')
	{
		if (*spec_arr == c)
		{
			return (1);
		}
		spec_arr++;
	}
	return (0);
}

/**
 * _set_spec_format - sets the character to the specification buffer
 * @c: character
 * @form_spec_buff: ptr to format specification buffer
 * Return: 1 if true, 0 else
 */
int _set_spec_format(char c, char *form_spec_buff)
{
	if (c == '\0')
	{
		form_spec_buff[0] = '\0';
		return (1);
	}
	/* set */
	form_spec_buff[0] = c, form_spec_buff[1] = '\0';
	return (1);
}

/**
 * is_format_spec - check if the ptr is a format specification, basic check
 * @str: src char ptr
 * @form_spec_buff: ptr to format specification buffer
 * @mods: ptr to ptr of modifiers
 * Return: 1 if it is, 0 if not
 */
int is_format_spec(const char *str, char *form_spec_buff,
	Modifiers_t *mods)
{
	int count;

	if (init_spec_chk(str) <= 0)
		return (init_spec_chk(str));
	count = 1;
	for (; str[count]; count++)
	{
		if (_is_format_spec_char(str[count]))
		{
			_set_spec_format(str[count], form_spec_buff);
			return (count);
		}
		else if (is_flag_character(str[count]))
		{/* if not set, set it */
			if (!is_flag_set(str[count], mods->flags))
				set_format_flag(str[count], mods->flags);
			continue;
		}
		else if (is_width_spec(str[count], str[count - 1], mods->width))
		{
			mods->width = atoi(&str[count]);
			continue;
		}
		else if (is_prec_spec(str[count], str[count + 1], mods->precision))
		{
			mods->precision = str[count + 1] - '0';
			continue;
		}
		else if (islmod(str[count], mods->length->long_m, mods->length->short_m))
		{
			if (str[count] == 'l')
				mods->length->long_m = 1;
			else
				mods->length->short_m = 1;
			continue;
		}
		else
			return (0);
	}
	return (-1);
}

/**
 * get_format_handler - gets the function used to print a specific format
 * @format_spec: the format spec
 * Return: 1 if it is, 0 if not
 */
Format_handler *get_format_handler(char *format_spec)
{
	int index;
	format_to_func_t type_list[] = {
		{"c", handle_char_format}, {"d", handle_int_format},
		{"s", handle_str_format}, {"f", handle_float_format},
		{"i", handle_int_format}, {"%", handle_percent_format},
		{"b", handle_bin_format}, {"u", handle_uint_format}
	};
	/* iterate */
	for (index = 0; index < (int) sizeof(format_to_func_t); index++)
	{
		/* if spec matches */
		if (*(type_list[index].format_type) == *format_spec)
		{
			return (type_list[index].format_func);
		}
	}

	return (NULL);
}

/**
 * print_invalid_format - ivalid format string, print flags and continue
 * @src_ptr: src char ptr
 * @buffer: print buffer
 * @buffer_i: buffer index
 * @mods: modifiers
 * @pr_count: count of items added to buffer
 * Return: the amt to push by
 */
int print_invalid_format_s(const char *src_ptr, char *buffer,
	int *buffer_i, Modifiers_t *mods, int *pr_count)
{
	int count = 0, index = 0;
	/* 100% invalid strig, print flags sequentially, flags->width->prec->len */
	add_to_buffer('%', buffer, buffer_i);
	*pr_count = *pr_count + 1, count++, index++;
	if (mods->flags->pound)
	{
		add_to_buffer('#', buffer, buffer_i);
		count += p_by(src_ptr, '#', index), *pr_count = *pr_count + 1;
	}
	if (mods->flags->plus)
	{
		add_to_buffer('+', buffer, buffer_i);
		count += p_by(src_ptr, '+', index), *pr_count = *pr_count + 1;
	}
	if (mods->flags->space)
	{
		count += p_by(src_ptr, ' ', index);
		if (!(mods->flags->plus))/* print a single space only if + not set */
			add_to_buffer(' ', buffer, buffer_i), *pr_count = *pr_count + 1;
	}
	if (mods->flags->minus)
	{
		add_to_buffer('-', buffer, buffer_i);
		count += p_by(src_ptr, '-', index), *pr_count = *pr_count + 1;
	}
	if (mods->flags->zero)
	{
		count += p_by(src_ptr, '0', index);
		if (!(mods->flags->minus))/* print a single 0 only if - not set */
			add_to_buffer('0', buffer, buffer_i), *pr_count = *pr_count + 1;
	}
	if (mods->width)
		count++;
	if (mods->precision)
		count += 2;
	handle_mod_lencheck(src_ptr, mods->length, &count, index);
	count = count > 0 ? count - 1 : count;
	return (count);
}
