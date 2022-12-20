#include "shell.h"

/**
 * process_cmds - process commands from shell data
 * @shell_d: pointer to shell data
 * Return: 0 if success, -1 else
 */
int process_cmds(shell_data_t *shell_d)
{
	cmd_prop_t *cmd = NULL;
	int ex_code = 0, i = 0;

	if (!shell_d || !shell_d->cmd_list)
		return (1);
	cmd = shell_d->cmd_list;

	/* iterate over each commd */
	for (i = 0; cmd; cmd = cmd->next, i++)
	{
		/* logical operators or split command eg |& */
		if ((cmd->flag == CMD_AND && ex_code != 0)
			|| (cmd->flag == CMD_OR && ex_code == 0))
		{
			shell_d->exit_code = ex_code;
			return (ex_code);
		}
		ex_code = handle_type_cmd(shell_d, cmd);
		shell_d->cmd_num = shell_d->cmd_num + i;
	}

	shell_d->exit_code = ex_code;
	return (ex_code);
}

/**
 * handle_type_cmd - a sub function to reduce main function line count
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: int
 */
int handle_type_cmd(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	alias_d_t *node = NULL;

	if (!cmd || !shell_d)
		return (0);
	/* empty cmd, blank line or tabs */
	if (!cmd->argc)
		return (0);

	if (is_builtin(cmd->argv[0]))
		return (proc_bin_cmd(shell_d, cmd));
	else if (is_alias_cmd(shell_d->alias_head, cmd->argv[0], &node))
		return (proc_alias_cmd(shell_d, cmd, node));
	else
		return (proc_ext_cmd(shell_d, cmd));
}

/**
 * get_bin_func - gets the handler func for builtins
 * @name: name of the builtin
 * Return: a pointer to a Bin_func
 */
int (*get_bin_func(char *name))(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	int i;

	bin_op_t builtin_l[] = {
		{"exit", Bin_exit},
		{"env", Bin_env},
		{"setenv", Bin_setenv},
		{"unsetenv", Bin_unsetenv},
		{"cd", Bin_cd},
		{"pwd", Bin_pwd}, {"alias", Bin_alias},
	};

	for (i = 0; i < 7; i++)
	{
		if (_strcmp(name, builtin_l[i].name) == 0)
			return (builtin_l[i].func);
	}

	return (NULL);
}

/**
 * proc_bin_cmd - process a builtin command
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: 0 on succss
 */
int proc_bin_cmd(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	Bin_func *handler;

	/* check */
	if (!cmd || !cmd->argv)
		return (BNF);
	/* get bin handler */
	handler = get_bin_func(cmd->argv[0]);
	if (!handler)
		return (CNF);
	return (handler(shell_d, cmd));
}

/**
 * proc_ext_cmd - process an external command process
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * Return: 0 on succss
 */
int proc_ext_cmd(shell_data_t *shell_d, cmd_prop_t *cmd)
{
	char *path = NULL;
	int ex_code = 0;
	/* check */
	if (!cmd || !cmd->argv)
		return (BNF);
	path = _which(cmd->argv[0]);
	if (!path)
	{
		errno = ENOENT, _print_err(shell_d, cmd, "not found\n");
		return (CNF);
	}
	ex_code = exec_cmd(path, cmd->argv), free(path);
	return (ex_code);
}
