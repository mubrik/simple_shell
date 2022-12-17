#include "shell.h"

/**
 * Bin_pwd - help debug
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_pwd(__attribute__((__unused__)) shell_data_t *shell_d,
	__attribute__((__unused__)) cmd_prop_t *cmd)
{
	buf path = NULL;

	path = _getenv("PWD");
	if (!path)
		return (0);
	_print(path, STDOUT_FILENO), _print("\n", STDOUT_FILENO);
	return (0);
}
