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
/* macros */
#define IN_BUFF_SIZE 1024

/* stucts and typedef */
/** buf - a buffer of type char *  */
typedef char *buf;

/**
 * enum mode - flag types
 * @INT: interactive mode
 * @NONINT: non interactive mode
 */
enum mode
{
	INT = 1 << 0,
	NONINT = 1 << 1
};

/* functions */
ssize_t get_input(char *buffer, u_long *n_bytes);
int set_buffers(char **input_b);
char **filter_argv(char **argv, int argc);

#endif /* MAIN_h */
