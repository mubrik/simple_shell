#ifndef MAIN_H
#define MAIN_H /* MAIN_h */

/* start */
#include "utils.h"
#include "token.h"
#include "which.h"
#include "exit.h"
#include "env.h"

/* macros */
#define IN_BUFF_SIZE 20
/**
 * is_builtin - checks if string is a built in arg
 * @s: ponter t string
 * Return: int
 */
static inline int is_builtin(char *s)
{ return ((_strcmp(s, "exit") == 0) || (_strcmp(s, "env") == 0)
	|| (_strcmp(s, "setenv") == 0) || (_strcmp(s, "unsetenv") == 0)); }

/* stucts and typedef */
/* This is a generic typedef for all the functions that handles commands */
typedef int Bin_handler(int argc, char *argv[]);
/* built in getter func */
Bin_handler (*get_b_in(char *name));
/** buf - a buffer of type char *  */
typedef char *buf;


/* functions */
ssize_t read_inputv(int fd, char **buffer, size_t n_bytes);
char **filter_argv(char **argv, int argc);
int exec_cmd(char *path, char **args);
int handle_ext(int argc, char *argv[]);
int handle_bin(int argc, char *argv[]);
int handle_p_exit(int ex_flag, char *main_name, int argc, char *arg_list[]);
int handle_cmd_type(int argc, char **argv);

/* new */

/* This is a generic typedef for all the functions that handles bin commands */
typedef int Bin_func(shell_data_t *shell_d, cmd_prop_t *cmd);
/* built in getter func */
Bin_func (*get_bin_func(char *name));

/**
 * struct builtin_op - struct holding built in name and func handler
 * @name: buitin name
 * @func: func
 */
typedef struct builtin_op
{
	char *name;
	Bin_func *func;
} builtin_op_t;

/* functions */

int init_shell_data(int argc, char **argv, shell_data_t *shell_d);
ssize_t get_input(int fd, shell_data_t *shell_d);
int process_data(shell_data_t *shell_d);
int ref_shell_data(shell_data_t *shell_d);
int process_cmds(shell_data_t *shell_d);
int handle_type_cmd(shell_data_t *shell_d, cmd_prop_t *cmd);
int proc_bin_cmd(shell_data_t *shell_d, cmd_prop_t *cmd);
int proc_ext_cmd(shell_data_t *shell_d, cmd_prop_t *cmd);

#endif /* MAIN_h */
