#ifndef WHICH_H
#define WHICH_H /* WHICH_H */

/* start */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../utils/utils.h"
/* env variables */
extern char **environ;
/* macros */
/**
 * is_path - checks if string is a pathname
 * @s: ponter t string
 * Return: int
 */
static inline int is_path(char *s) { return ((s[0] == '.') || (s[0] == '/')); }

/**
 * struct which_list - list of filename path in PATH
 * @path: the path to the file
 * @next: pointer to next struct
 * @prev: pointer to prev struct
 */
typedef struct which_list
{
	char *path;
	struct which_list *next;
	struct which_list *prev;
} which_list_t;

/* functions */
char *_getenv(char *name);
void free_list_wl(which_list_t *head);
which_list_t *tokenize_wl(char *input_b, char *pathname,
	char *delim, which_list_t **path_list);
which_list_t *add_node_wl(which_list_t **head, char *str);
which_list_t *add_node_end_wl(which_list_t **head, char *str);
which_list_t *_which(char *filename);

#endif /* WHICH_H */
