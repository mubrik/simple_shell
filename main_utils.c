#include "main.h"

/**
 * filter_argv - filters out he progrma name from argv into a new buffer
 * @argv: argv buffer
 * @argc: argument count
 * Return: a pointer to array of char*
 */
char **filter_argv(char **argv, int argc)
{
	int i;
	char **arr;

	if (!argc || !argv)
		return (NULL);

	arr = malloc(sizeof(char *) * argc);
	if (!arr)
		return (NULL);

	for (i = 0; i <= argc; i++)
	{
		if (i == 0) /* skip program name */
			continue;
		if (i == argc)
		{ /* add last null and break loop */
			arr[i - 1] = NULL;
			break;
		}
		arr[i - 1] = argv[i];
	}

	return (arr);
}

/**
 * get_b_in - gets the handler func for builtins
 * @name: name of the builtin
 * Return: a pointer to builtin_op_t
 */
int (*get_b_in(char *name))(int argc, char *argv[], char *env[])
{
	int i;

	builtin_op_t builtin_l[] = {
		{"exit", bin_exit},
		{"env", bin_env},
		{"setenv", bin_setenv},
		{"unsetenv", bin_unsetenv},
	};

	for (i = 0; i < 4; i++)
	{
		if (_strcmp(name, builtin_l[i].name) == 0)
			return (builtin_l[i].func);
	}

	return (NULL);
}

/**
 * handle_bin - handles a builtin command process
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: 0 on succss
 */
int handle_bin(int argc, char **argv[], char *env[])
{
	Bin_handler *handler;
	char **arg_list = *argv;
	/* check */
	if (!arg_list || !env)
		return (BNF);
	/* get bin handler */
	handler = get_b_in(arg_list[0]);
	if (!handler)
		return (CNF);
	return (handler(argc, arg_list, env));
}

/**
 * handle_ext - handles an ext command process
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: 0 on succss
 */
int handle_ext(__attribute_maybe_unused__ int argc, char **argv[], char *env[])
{
	which_list_t *path_list = NULL;
	char **arg_list = *argv;
	/* check */
	if (!arg_list || !env)
		return (BNF);
	path_list = _which(arg_list[0]);
	if (!path_list)
		return (CNF);
	exec_cmd(path_list->path, arg_list, env), free_list_wl(path_list);
	return (0);
}

/**
 * handle_p_exit - handles the exit code of a bin or ext program command
 * @ex_flag: exit_flag
 * @main_name: the main program name
 * @argc: the arg_list count
 * @arg_list: the arg_list
 * @env: the env
 * Return: 0 on succss
 */
int handle_p_exit(int ex_flag, __attribute_maybe_unused__ char *main_name,
	__attribute_maybe_unused__ int argc, __attribute_maybe_unused__ char *arg_list[],
	__attribute_maybe_unused__ char *env[])
{
	printf("ex flag: %d\n", ex_flag);
	if (!ex_flag)
		return (0);
	switch (ex_flag)
	{
		case CNF:
			_print("No such file or directory\n", STDERR_FILENO);
			return (0);
		case ANV:
			_print("Argument not valid\n", STDERR_FILENO);
			return (0);
		case FNF :
			_print("No such file or directory\n", STDERR_FILENO);
			return (0);
		case BNF:
			_print("No Buffer\n", STDERR_FILENO);
			return (0);
		default:
			return (0);
	}
}