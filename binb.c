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
	buf name = NULL, val = NULL, delim = "=";
	int index = 0;

	if (cmd->argc <= 1)
	{
		print_aliaslist(shell_d->alias_head, NULL);
		return (0);
	}
	for (index = 1; index < cmd->argc; index++)
	{
		/* get the values */
		name = _strtok(cmd->argv[index], delim), val = _strtok(NULL, delim);
		if (!name)
			break;
		if (!val)
		{
			/* print the filtered name vals*/
			print_aliaslist(shell_d->alias_head, name);
			continue;
		}
		/* name + value, check exist */
		node = get_alias_node(shell_d->alias_head, name);
		if (!node)
			add_node_alias_end(&(shell_d->alias_head), name, val);
		else
		{
			/* replace */
			free(node->value), node->value = _strdup(val);
		}
	}
	return (0);
}
