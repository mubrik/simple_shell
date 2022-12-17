#include "shell.h"

/**
 * Bin_exit - main function int argc, char *argv[], char *env[]
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_exit( __attribute__((__unused__)) shell_data_t *shell_d, cmd_prop_t *cmd)
{
	int ex_code = 0;

	if (cmd->argc <= 1)
		exit(EXIT_SUCCESS);
	if (!cmd->argv[1])
		exit(EXIT_SUCCESS);
	/* convert arg to int, unsafe */
	ex_code = _atoi(cmd->argv[1]);
	exit(ex_code);
}
