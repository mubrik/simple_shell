#ifndef UTIL_H
#define UTIL_H /* UTIL_H */

#include <stdlib.h>
#include <stdarg.h>

int _strlen(const char *src_ptr);
int _memcpy(const char *src, char *dest);
int _strocr(const char *str_ptr, char c);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
char *_strconcat(const char *src, const char *add_str);
char *_strconcatv(const char *src, unsigned int count, ...);

#endif /* UTIL_H */
