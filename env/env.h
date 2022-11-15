#ifndef ENV_H
#define ENV_H /* ENV_H */

/* start */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../utils/utils.h"

/* functions */
int bin_env(int argc, char *argv[], char *env[]);
int bin_setenv(int argc, char  *argv[], char *env[]);
int bin_unsetenv(int argc, char *argv[], char *env[]);

#endif /* ENV_H */