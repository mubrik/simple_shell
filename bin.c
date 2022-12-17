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
		_print_err(shell_d, cmd, "Illegal number: ");
		_print(cmd->argv[1], STDERR_FILENO);
		_print("\n", STDERR_FILENO), ex_code = 2;
	}
	else if (ex_code < 0)
	{
		_print_err(shell_d, cmd, "Illegal number: ");
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
		return (0);
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
		return (0);
	return (_unsetenv(cmd->argv[1]));
}

/**
 * Bin_cd - change dir function
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_cd(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	int ex_code = 0, go_back = 0;
	buf curr_path = NULL, path = NULL;

	if (cmd->argc == 1 || !cmd->argv[1])
		path = _getenv("HOME"); /* if no arg */
	else if (_strcmp(cmd->argv[1], "-") == 0)
		path = _getenv("OLDPWD"), go_back = 1; /* if - */
	else
		path = cmd->argv[1];
	if (!path)
		return (0);
	curr_path = malloc(sizeof(char) * CD_B);
	if (!curr_path)
		return (0);
	/* save curr pwd */
	getcwd(curr_path, CD_B);
	if (go_back && path)
		_print(path, STDOUT_FILENO), _print("\n", STDOUT_FILENO);
	/* switch */
	ex_code = chdir(path);
	if (ex_code != 0)
	{
		/* error occured */
		ex_code = errno, perror(shell_d->shell_argv[0]), free(curr_path);
		return (ex_code);
	}
	/* update old path */
	_setenv("OLDPWD", curr_path, 1);
	/* get new path */
	getcwd(curr_path, CD_B);
	/* update path */
	ex_code = _setenv("PWD", curr_path, 1), free(curr_path);
	return (ex_code);
}
