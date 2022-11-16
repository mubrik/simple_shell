#ifndef MAIN_h
#define MAIN_h /* MAIN_h */

/* start */
#include "utils.h"
#include "token.h"
#include "which.h"
#include "exit.h"
#include "env.h"

/* macros */
#define IN_BUFF_SIZE 1024

/* stucts and typedef */
/* This is a generic typedef for all the functions that handles commands */
typedef int Bin_handler(int argc, char *argv[]);
/* built in getter func */
Bin_handler (*get_b_in(char *name));
/** buf - a buffer of type char *  */
typedef char *buf;
/**
 * struct builtin_op - struct holding built in name and func handler
 * @name: buitin name
 * @func: func
 */
typedef struct builtin_op
{
	char *name;
	Bin_handler *func;
} builtin_op_t;


/* functions */
ssize_t read_input(int fd, char *buffer, size_t n_bytes);
int set_buffers(char **input_b);
char **filter_argv(char **argv, int argc);
int exec_cmd(char *path, char **args);
int handle_ext(int argc, char **argv[]);
int handle_bin(int argc, char **argv[]);
int handle_p_exit(int ex_flag, char *main_name, int argc, char *arg_list[]);

/**
 * is_builtin - checks if string is a built in arg
 * @s: ponter t string
 * Return: int
 */
static inline int is_builtin(char *s)
{ return ((_strcmp(s, "exit") == 0) || (_strcmp(s, "env") == 0)
	|| (_strcmp(s, "setenv") == 0) || (_strcmp(s, "unsetenv") == 0)); }

#endif /* MAIN_h */
