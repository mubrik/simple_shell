#ifndef UTIL_H
#define UTIL_H /* UTIL_H */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* print buffer size */
#define P_BUFF_SIZE 1024

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
	CNF = 1 << 0,
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
int _strocr(const char *str_ptr, char c);
int _strcmp(const char *s1_ptr, const char *s2_ptr);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
char *_strconcat(const char *src, const char *add_str);
/* char *_strconcatv(const char *src, unsigned int count, ...); */
char *_strconcatd(const char *src, const char *adda, const char *addb);
char *_strchr(char *str_ptr, char c);
char *_strtok(char *str, char *delim);

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
