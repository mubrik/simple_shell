#ifndef SHELL_H
#define SHELL_H /* SHELL_H */

/* start */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/* macros */
#define IN_BUFF_SIZE 20
/* print buffer size */
#define P_BUFF_SIZE 1024
/* cd path buffer */
#define CD_B 4028
/* p arr size */
#define P_AR 50

/** buf - a buffer of type char *  */
typedef char *buf;

/* structs and enums */

/**
 * enum cmd_op_flag - command operator flag
 * @CMD_AND: run command if last exit success
 * @CMD_OR: run command only if prev fail
 * @CMD_NL: Newline run command unconditionally
 */
typedef enum cmd_op_flag
{ CMD_AND = 0, CMD_OR = 1 << 0, CMD_NL = 1 << 1} cmd_op_flag_t;

/**
 * enum ex_flag - exit flags for bin or ext commands
 * @OK: ok
 * @CNF: command not found
 * @FNF: file not found
 * @BNF: Buffer not found
 * @ANV: Command arguments not valid
 * @INV: Invalid Operation?
 */
typedef enum ex_flag
{
	OK = 0,
	CNF = 127 << 0,
	FNF = 1 << 1,
	BNF = 1 << 2,
	ANV = 1 << 3,
	INV = 1 << 4
} ex_flag_t;

/**
 * struct cmd_prop - commands and properties
 * @cmd: the command, null terminated string
 * @argv: pointer to argv arr
 * @argc: arg count
 * @flag: the flag/type of the token
 * @next: pointer to next token
 * @prev: pointer to prev token
 */
typedef struct cmd_prop
{
	char *cmd;
	char **argv;
	int argc;
	cmd_op_flag_t flag;
	struct cmd_prop *next;
	struct cmd_prop *prev;
} cmd_prop_t;

/**
 * struct arg_list - list of tokenized args
 * @token: the token, null terminated string
 * @next: pointer to next token
 * @prev: pointer to prev token
 */
typedef struct arg_list
{
	char *token;
	struct arg_list *next;
	struct arg_list *prev;
} arg_list_t;

/**
 * struct alias_d - a node for alias_type
 * @name: alias name
 * @value: alias value
 * @next: pointer to next token
 * @prev: pointer to prev token
 */
typedef struct alias_d
{
	char *name;
	char *value;
	struct alias_d *next;
	struct alias_d *prev;
} alias_d_t;

/**
 * struct shell_data - hold necessary shell data
 * @exit_code: exit code
 * @cmd_num: the index of current command
 * @i_mode: intercative mode
 * @s_pid: shell pid
 * @input_buff: the main inpu buffer, malloc'd
 * @cmd_list: doubly linked command cmd_prop_t list
 * @alias_head: head of doubly linked alias_d_t list
 * @shell_argc: argc of shell
 * @shell_argv: ptr argv of shell
 * @p_arr: rray of pointers to be freed at exit
 */
typedef struct shell_data
{
	int exit_code;
	int cmd_num;
	int i_mode;
	pid_t s_pid;
	char *input_buff;
	cmd_prop_t *cmd_list;
	alias_d_t *alias_head;
	int shell_argc;
	char **shell_argv;
	buf *p_arr;
} shell_data_t;

/* This is a generic typedef for all the functions that handles bin commands */
typedef int Bin_func(shell_data_t *shell_d, cmd_prop_t *cmd);

/**
 * struct bin_op - struct holding built in name and func handler
 * @name: buitin name
 * @func: func
 */
typedef struct bin_op
{
	char *name;
	Bin_func *func;
} bin_op_t;


/* env variables */

extern char **environ;
int is_env_change(int incr);

/* main functions */

ssize_t get_input(int fd, shell_data_t *shell_d);
int init_shell_data(int argc, char **argv, shell_data_t *shell_d);
int process_data(shell_data_t *shell_d);
int ref_shell_data(shell_data_t *shell_d);
int free_shell_data(shell_data_t *shell_d);
int add_to_p_arr(shell_data_t *shell_d, buf ptr);

/* cmd _functions */

int process_cmds(shell_data_t *shell_d);
int handle_type_cmd(shell_data_t *shell_d, cmd_prop_t *cmd);
int proc_bin_cmd(shell_data_t *shell_d, cmd_prop_t *cmd);
int proc_ext_cmd(shell_data_t *shell_d, cmd_prop_t *cmd);
int proc_alias_cmd(shell_data_t *shell_d,
	cmd_prop_t *cmd, alias_d_t *alias);
int exec_cmd(char *path, char **args);

/* built ins */

Bin_func Bin_exit;
Bin_func Bin_env;
Bin_func Bin_setenv;
Bin_func Bin_unsetenv;
Bin_func Bin_cd;
Bin_func Bin_pwd;
Bin_func Bin_alias;

/* string functions */

int _strlen(const char *src_ptr);
int _atoi(char *s);
int _memcpy(const char *src, char *dest);
char *_str_realloc(char *src, size_t buf_size, size_t size_n);
int _strocr(const char *str_ptr, char c);
int _strcmp(const char *s1_ptr, const char *s2_ptr);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *src_ptr, char *dest_ptr, int n);
char *_strdup(const char *src);
char *_strconcat(const char *src, const char *add_str);
char *_strconcatd(const char *src, const char *adda, const char *addb);
char *_strchr(char *str_ptr, char c);
char *_strtok(char *str, char *delim);
char *_strtok_r(char *str, char *delim, char **saveptr);
unsigned int _strspn(char *src, char *accept);
char *_itoa(int value, char *result, int base);

/* cmd_list functions */

cmd_prop_t *add_node_cmd_end(cmd_prop_t **head, char *buf, int n);
size_t cmdlist_len(const cmd_prop_t *head);
size_t print_cmdlist(const cmd_prop_t *head);
int inp_tok(char *buffer, cmd_prop_t **head);
void free_cmdlist(cmd_prop_t *head);

/* arg_list functions */

char **arg_tok(char *input_b, char *delim, int *l_size);
arg_list_t *add_node_argl_end(arg_list_t **head, char *str);
void free_arg_list(arg_list_t *head);
int cmd_to_args(shell_data_t *shell_d);
int print_args_cmdlist(cmd_prop_t *cmd_list);
int var_substitute(shell_data_t *shell_d, char **argv, int argc);

/* alias */
/* would have been better with hashtable? */

alias_d_t *add_node_alias_end(alias_d_t **head, char *name, char *value);
size_t aliaslist_len(const alias_d_t *head);
size_t print_aliaslist(alias_d_t *head, char *cmp);
void free_aliaslist(alias_d_t *head);
alias_d_t *get_alias_node(alias_d_t *head, char *name);
int is_alias_cmd(alias_d_t *head, char *name, alias_d_t **node);

/* which */

char *_which(char *command);

/* list func */

int lst_size(char **arr);
int free_lst(char **arr);

/* print functions */

int _print(const char *string, int fd);
int _print_num(int num, int fd);
int _print_err(shell_data_t *shell_d, cmd_prop_t *cmd, char *err);
int print_buffer(int fd, char *buffer, int byte_count);
int add_to_buffer(int fd, char str, char *buffer, int *buffer_i);

/* env functions */

char *_is_in_env(char *name);
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

/* built in getter func */

Bin_func (*get_bin_func(char *name));

/* inline functions */

/**
 * is_builtin - checks if string is a built in arg
 * @s: ponter t string
 * Return: int
 */
static inline int is_builtin(char *s)
{ return ((_strcmp(s, "exit") == 0) || (_strcmp(s, "env") == 0)
	|| (_strcmp(s, "setenv") == 0) || (_strcmp(s, "unsetenv") == 0)
	|| (_strcmp(s, "cd") == 0) || (_strcmp(s, "pwd") == 0)
	|| (_strcmp(s, "alias") == 0)); }

/**
 * is_path - checks if string is a pathname
 * @s: ponter t string
 * Return: int
 */
static inline int is_path(char *s) { return ((s[0] == '.') || (s[0] == '/')); }

#endif /* SHELL_H */
