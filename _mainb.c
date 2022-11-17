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
int (*get_b_in(char *name))(int argc, char *argv[])
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
 * Return: 0 on succss
 */
int handle_bin(int argc, char **argv[])
{
	Bin_handler *handler;
	char **arg_list = *argv;
	/* check */
	if (!arg_list)
		return (BNF);
	/* get bin handler */
	handler = get_b_in(arg_list[0]);
	if (!handler)
		return (CNF);
	return (handler(argc, arg_list));
}

/**
 * handle_ext - handles an ext command process
 * @argc: argument count
 * @argv: array of char argument values
 * Return: 0 on succss
 */
int handle_ext(__attribute__((unused)) int argc, char **argv[])
{
	char *path = NULL;
	char **arg_list = *argv;
	/* check */
	if (!arg_list)
		return (BNF);
	path = _which(arg_list[0]);
	if (!path)
		return (CNF);
	exec_cmd(path, arg_list), free(path);
	return (0);
}

/**
 * handle_p_exit - handles the exit code of a bin or ext program command
 * @ex_flag: exit_flag
 * @main_name: the main program name
 * @argc: the arg_list count
 * @arg_list: the arg_list
 * Return: 0 on succss
 */
int handle_p_exit(int ex_flag, __attribute__((unused)) char *main_name,
	int argc, char *arg_list[])
{
	if (ex_flag < 0 || !ex_flag)
		return (ex_flag);

	switch (ex_flag)
	{
		case CNF:
			if (argc > 0)
				_print(arg_list[0], STDERR_FILENO), _print(": ", STDERR_FILENO);
			_print("Command not Found\n", STDERR_FILENO);
			return (0);
		case ANV:
			if (argc >= 1)
				_print(arg_list[1], STDERR_FILENO), _print(": ", STDERR_FILENO);
			_print("Argument not valid\n", STDERR_FILENO);
			return (0);
		case FNF:
			if (argc > 0)
				_print(arg_list[0], STDERR_FILENO), _print(": ", STDERR_FILENO);
			_print("No such file or directory\n", STDERR_FILENO);
			return (0);
		case BNF:
			_print("No Buffer\n", STDERR_FILENO);
			return (0);
		default:
			return (0);
	}
}
