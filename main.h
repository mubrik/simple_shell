#ifndef MAIN_h
#define MAIN_h /* MAIN_h */

/* start */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* custom */
#include "./utils/utils.h"
#include "./token/token.h"
#include "./which/which.h"
#include "./exit/exit.h"
#include "./env/env.h"
/* macros */
#define IN_BUFF_SIZE 1024

/* stucts and typedef */
/* This is a generic typedef for all the functions that handles commands */
typedef int Bin_handler(int argc, char *argv[], char *env[]);
/* built in getter func */
Bin_handler (*get_b_in(char *name));
/** buf - a buffer of type char *  */
typedef char *buf;
/**
 * struct builtin_op - struct holding built in name and func handler
 * @name: bbuitin name
 * @func: pointer to func handler
 */
typedef struct builtin_op
{
	char *name;
	Bin_handler (*func);
} builtin_op_t;

/**
 * enum ex_flag - exit flags for bin or ext commands
 * @OK: ok
 * @CNF: command not found
 * @FNF: file not found
 * @BNF: Buffer not found
 * @ANV: Command arguments not valid
 */
typedef enum ex_flag
{
	OK = 0,
	CNF = 1 << 0,
	FNF = 1 << 1,
	BNF = 1 << 2,
	ANV = 1 << 3
} ex_flag_t;

/* functions */
ssize_t get_input(char *buffer, u_long *n_bytes);
int set_buffers(char **input_b);
char **filter_argv(char **argv, int argc);
int exec_cmd(char *path, char **args, char **env);
int handle_ext(int argc, char **argv[], char *env[]);
int handle_bin(int argc, char **argv[], char *env[]);
int handle_p_exit(int ex_flag, char *main_name,
	int argc, char *arg_list[], char *env[]);

/**
 * is_builtin - checks if string is a built in arg
 * @s: ponter t string
 * Return: int
 */
static inline int is_builtin(char *s)
{ return ((_strcmp(s, "exit") == 0) || (_strcmp(s, "env") == 0)
	|| (_strcmp(s, "setenv") == 0) || (_strcmp(s, "unsetenv") == 0)); }



#endif /* MAIN_h */
