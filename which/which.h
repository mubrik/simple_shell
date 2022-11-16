#ifndef WHICH_H
#define WHICH_H /* WHICH_H */

/* start */
#include "../utils/utils.h"

/* macros */
/**
 * is_path - checks if string is a pathname
 * @s: ponter t string
 * Return: int
 */
static inline int is_path(char *s) { return ((s[0] == '.') || (s[0] == '/')); }

char *_which(char *command);

#endif /* WHICH_H */
