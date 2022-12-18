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

/**
 * Bin_alias - alias command
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int Bin_alias(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	alias_d_t *node = NULL;

	if (cmd->argc <= 1)
	{
		print_aliaslist(shell_d->alias_head, NULL);
		return (0);
	}
	else if (cmd->argc == 2 && cmd->argv[1])
	{
		/* print filtered */
		print_aliaslist(shell_d->alias_head, cmd->argv[1]);
		return (0);
	}
	/* name + value */
	/* check if exist */
	node = get_alias_node(shell_d->alias_head, cmd->argv[1]);
	if (!node)
		add_node_alias_end(&(shell_d->alias_head), cmd->argv[1], cmd->argv[2]);
	else
	{
		/* replace */
		free(node->value), node->value = _strdup(cmd->argv[2]);
	}

	return (0);
}

