#include "shell.h"

/**
 * Bin_exit - main function int argc, char *argv[], char *env[]
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_exit(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	int ex_code = 0;

	if (cmd->argc <= 1 || !cmd->argv[1])
	{
		/* get prev command ex code and free shell data */
		ex_code = shell_d->exit_code, free_shell_data(shell_d);
		if (ex_code)
			exit(ex_code);
		exit(EXIT_SUCCESS);
	}
	/* convert arg to int, unsafe */
	ex_code = _atoi(cmd->argv[1]);
	if (ex_code == 0) /* most likely illegal */
	{
		_print_err(shell_d, cmd, "illegal number:");
		_print(cmd->argv[1], STDERR_FILENO);
		_print("\n", STDERR_FILENO), ex_code = 2;
	}
	else if (ex_code < 0)
	{
		_print_err(shell_d, cmd, "illegal number:");
		_print_num(ex_code, STDERR_FILENO);
		_print("\n", STDERR_FILENO), ex_code = 2;
	}
	free_shell_data(shell_d), exit(ex_code);
}

/**
 * Bin_env - env func
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_env(__attribute__((__unused__)) shell_data_t *shell_d,
	cmd_prop_t *cmd)
{
	unsigned int i = 0;

	if (cmd->argc < 0)
		return (INV);
	for (i = 0; environ[i]; i++)
	{
		_print(environ[i], _STDIO_H), _print("\n", _STDIO_H);
	}
	return (0);
}

/**
 * Bin_setenv - env func
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_setenv(__attribute__((__unused__)) shell_data_t *shell_d,
	cmd_prop_t *cmd)
{

	/* check */
	if (cmd->argc < 3)
		return (ANV);
	return (_setenv(cmd->argv[1], cmd->argv[2], 1));
}

/**
 * Bin_unsetenv - env func
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_unsetenv(__attribute__((__unused__)) shell_data_t *shell_d,
	cmd_prop_t *cmd)
{

	/* check */
	if (cmd->argc < 2)
		return (ANV);
	return (_unsetenv(cmd->argv[1]));
}
