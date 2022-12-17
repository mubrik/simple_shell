#ifndef UTIL_H
#define UTIL_H /* UTIL_H */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/* print buffer size */
#define P_BUFF_SIZE 1024

/**
 * enum cmd_op_flag - command operator flag
 * @CMD_AND: run command if last exit success
 * @CMD_OR: run command unconditionally
 */
typedef enum cmd_op_flag
{ CMD_AND = 0, CMD_OR = 0 < 1} cmd_op_flag_t;

/**
 * struct cmd_prop - commands and property
 * @cmd: the command, null terminated string
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
 * struct arg_list_t - list of tokenized args
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
 * struct shell_data_t - hold necessary shell data
 * @exit_code: exit code
 * @cmd_num: the index of current command
 * @i_mode: intercative mode
 * @input_buff: the main inpu buffer, malloc'd
 * @cmd_list: doubly linked command cmd_prop_t list
 * @shell_argc: argc of shell
 * @shell_argv: ptr argv of shell
 */
typedef struct shell_data
{
	int exit_code;
	int cmd_num;
	int i_mode;
	char *input_buff;
	cmd_prop_t *cmd_list;
	int shell_argc;
	char **shell_argv;
} shell_data_t;


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

/* env variables */

extern char **environ;
int is_env_change(int incr);

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

/* list func */

int lst_size(char **arr);
int free_lst(char **arr);

/* print functions */

int _print(const char *string, int fd);
int print_buffer(int fd, char *buffer, int byte_count);
int add_to_buffer(int fd, char str, char *buffer, int *buffer_i);

/* env functions */

char *_is_in_env(char *name);
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

#endif /* UTIL_H */
