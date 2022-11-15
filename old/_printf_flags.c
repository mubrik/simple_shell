#include "printf.h"

/**
 * is_flag_set - checks if a flag is set
 * Return: 1 if set, 0 if not
 * @flag: flag character or 'n' for number
 * @format_flag: the format flag struct ptr
 */
int is_flag_set(char flag, Format_flag_t *format_flag)
{
	if (!format_flag)
		return (0);

	switch (flag)
	{
	case '+':
		return (format_flag->plus);
	case '-':
		return (format_flag->minus);
	case ' ':
		return (format_flag->space);
	case '#':
		return (format_flag->pound);
	case '0':
		return (format_flag->zero);
	default:
		return (1);
	}
}

/**
 * set_format_flag - sets a format flag
 * Return: 1 if set, 0 if not
 * @flag: flag character or 'n' for number
 * @format_flag: the format flag struct ptr
 */
int set_format_flag(char flag, Format_flag_t *format_flag)
{
	if (!format_flag)
		return (0);

	switch (flag)
	{
	case '+':
		format_flag->plus = 1;
		return (1);
	case '-':
		format_flag->minus = 1;
		return (1);
	case ' ':
		format_flag->space = 1;
		return (1);
	case '#':
		format_flag->pound = 1;
		return (1);
	case '0':
		format_flag->zero = 1;
		return (1);
	default:
		return (1);
	}
}

/**
 * reset_format_flag - resets all flags to 0
 * @format_flag: the format flag struct ptr
 * Return: ptr to format flag
 */
Format_flag_t *reset_format_flag(Format_flag_t *format_flag)
{
	if (!format_flag)
		return (NULL);
	/* set flasg/attribs */
	format_flag->minus = 0, format_flag->zero = 0;
	format_flag->plus = 0, format_flag->space = 0, format_flag->pound = 0;
	return (format_flag);
}

/**
 * is_mods_set - checks all mods if any was set
 * @mods: tptr to modifiers
 * Return: 1 if true, 0 else
 */
int is_mods_set(Modifiers_t *mods)
{
	if ((mods->precision) || (mods->width) || (mods->length->long_m) ||
		(mods->length->short_m || (mods->flags->minus) || (mods->flags->plus)) ||
		(mods->flags->pound) || (mods->flags->space) || (mods->flags->zero))
	{
		return (1);
	}
	return (0);
}
