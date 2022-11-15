#ifndef UTIL_H
#define UTIL_H /* UTIL_H */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

/* print buffer size */
#define P_BUFF_SIZE 1024

/* env variables */

extern char **environ;

/* string functions */

int _strlen(const char *src_ptr);
int _atoi(char *s);
int _memcpy(const char *src, char *dest);
int _strocr(const char *str_ptr, char c);
int _strcmp(const char *s1_ptr, const char *s2_ptr);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
char *_strconcat(const char *src, const char *add_str);
char *_strconcatv(const char *src, unsigned int count, ...);
char *_strchr(char *str_ptr, char c);
char *_str_tok(char *str, char *delim);

/* list func */

int lst_size(char **arr);

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
