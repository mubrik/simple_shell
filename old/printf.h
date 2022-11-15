#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* buffer size of printf */
#define PRINT_BUFF_SIZE 1024

/**
 * struct Format_flag - holds the array of flags
 * @plus: 1 if flag is set, 0 otherwise
 * @minus: 1 if flag is set, 0 otherwise
 * @space: 1 if flag is set, 0 otherwise
 * @pound: 1 if flag is set, 0 otherwise
 * @zero: 1 if flag is set, 0 otherwise
 * Description: Betty forced me to use a typedef here, the array of flags
 */
typedef struct Format_flag
{
	unsigned int plus;
	unsigned int minus;
	unsigned int space;
	unsigned int pound;
	unsigned int zero;
} Format_flag_t;

/**
 * struct Length_mod - holds the legth modifiers
 * @long_m: 1 if modifier is set, 0 otherwise
 * @short_m: 1 if modifier is set, 0 otherwise
 */
typedef struct Length_mod
{
	unsigned int long_m;
	unsigned int short_m;
} Length_mod_t;

/**
 * struct Modifiers - holds all modifiers for a spec, flags, width, len, prec.
 * @flags: pointer to the flags struct
 * @length: pointer to the lenght struct
 * @width: num of width, 0 if no width set
 * @precision: num of precision, 0 if none set set
 */
typedef struct Modifiers
{
	Format_flag_t *flags;
	Length_mod_t *length;
	unsigned int width;
	unsigned int precision;
} Modifiers_t;

/* This is a generic typedef for all the functions that handles a format spc */
typedef int Format_handler(va_list arg_list, char *buffer,
	int *buffer_i, Modifiers_t *mods);

/* functions that handle a spec format */
Format_handler handle_char_format;
Format_handler handle_str_format;
Format_handler handle_int_format;
Format_handler handle_uint_format;
Format_handler handle_float_format;
Format_handler handle_percent_format;
Format_handler handle_bin_format;
Format_handler *get_format_handler(char *spec); /* ptr to func ptr */

/**
 * struct format_to_func - this holds a char ptr and func ptr
 * @format_type: format type/name
 * @format_func: ptr to func of operation
 * Description: Betty forced me to use a typedef here
 */
typedef struct format_to_func
{
	char *format_type;
	Format_handler (*format_func);
} format_to_func_t;

/* major func, checs if string is format spec */
int is_format_spec(const char *src_ptr, char *s_buff, Modifiers_t *mods);
int print_invalid_format_s(const char *src_ptr,
	char *buffer, int *buffer_i, Modifiers_t *mods, int *pr_count);

/* buffer functions */
int print_buffer(char *buffer, int byte_count);
int add_to_buffer(char str, char *buffer, int *buffer_i);
int add_int_buff(unsigned int num, char *buffer, int *buffer_i);
int add_long_int_buff(unsigned long int num, char *buffer, int *buffer_i);
int free_buff_mem(int num, ...);
int allocate_buff_mem(char **pr_buff, int **pr_buff_index,
	char **format_spec_buff, Modifiers_t **mods);
void int_to_hex_buff(unsigned int integer, char *bin_b, int num);

/* inlinee */
/**
 * is_number - checks if char is a number
 * @c: character
 * Return: 1 if true, 0 else
 */
static inline int is_number(char c) { return (c >= '0' && c <= '9'); }
/**
 * is_flag_character - checks if char is a flag type ( +-0)
 * @c: character
 * Return: 1 if true, 0 else
 */
static inline int is_flag_character(char c)
{ return (c == ' ' || c == '+' || c == '-' || c == '#' || c == '0'); }
/**
 * islmod - checks len modify
 * @c: ptr to strin
 * @long_l: len modifier
 * @short_s: ptr to cou
 * Return: int
 */
static inline int islmod(char c, int long_l, int short_s)
{ return ((c == 'l' || c == 'h') && !(long_l) && !(short_s)); }

/**
 * is_prec_spec - chec prec spec
 * @c: ptr to strin
 * @next: len modifier
 * @precision: ptr to count
 * Return: int
 */
static inline int is_prec_spec(char c, char next, int precision)
{ return (c == '.' && is_number(next) && !(precision)); }

/**
 * is_width_spec - checks width
 * @c: ptr to strin
 * @prev: len modifier
 * @width: ptr to cou
 * Return: int
 */
static inline int is_width_spec(char c, char prev, int width)
{ return (is_number(c) && c != '0' && prev == '.' && !(width)); }

/* utility functions */
/* int is_number(char c); */
void capitalize_alpha(char *src_ptr);
int is_non_printable(char *src_ptr);
int atoi_m(char *s);
int reset_mods(Modifiers_t *mods);
int p_by(const char *src_ptr, char c, int index);
/* extras */
void handle_mod_lencheck(const char *format, Length_mod_t *len,
	int *count, int index);
void long_int_to_hex_buff(unsigned long int integer, char *bin_b, int num);
void long_int_to_oct_buff(unsigned long int integer, char *bin_b, int num);
int is_prec_spec(char c, char next, int precision);
int is_width_spec(char c, char prev, int width);
int islmod(char c, int long_l, int short_s);
int init_spec_chk(const char *str);
/* flag functions */
int is_flag_set(char flag, Format_flag_t *format_flag);
int is_flag_character(char c);
int set_format_flag(char flag, Format_flag_t *format_flag);
Format_flag_t *reset_format_flag(Format_flag_t *format_flag);
int is_mods_set(Modifiers_t *mods);

/* main */
int _printf(const char *format, ...);
int _perror(unsigned int count, ...);

#endif /* MAIN_H */
