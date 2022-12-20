#include "shell.h"

/**
 * proc_alias_cmd - process an alias command process
 * @shell_d: shell data
 * @cmd: ptr tocmd cmd_prop_t
 * @alias: alais node
 * Return: 0 on succss
 */
int proc_alias_cmd(shell_data_t *shell_d,
	__attribute__((__unused__)) cmd_prop_t *cmd, alias_d_t *alias)
{
	alias_d_t *node = NULL, *tmp = NULL;
	buf value = NULL, *arr = NULL, str = NULL;
	int l_size = 0, ex_code;

	if (!shell_d || !alias)
		return (0);
	node = alias;
	/* check if value of alais, is an alias */
	while (node)
	{
		value = node->value;
		tmp = get_alias_node(alias, value);
		if (!tmp)
			break;
		node = tmp;
	}
	/* dup string to avoaid tokenizing alias value */
	str = _strdup(node->value), arr = arg_tok(str, " \t", &l_size);
	if (!arr)
		return (0);
	ex_code = exec_cmd(str, arr), free(str);
	return (ex_code);
}

/**
 * exec_cmd - main function int argc, char *argv[], char *env[]
 * @path: argument count
 * @args: array of char argument values
 * Return: int
 */
int exec_cmd(char *path, char **args)
{
	int c_pid, c_status;
	/* check */
	if (!path || !args)
		return (-1);
	c_pid = fork();
	if (c_pid == -1)
		return (-1);
	else if (c_pid > 0)
	{
		do {
			waitpid(c_pid, &c_status, WUNTRACED); /* man 2 waitpid */
		} while (!WIFEXITED(c_status)
			&& !WIFSIGNALED(c_status) && !WIFSTOPPED(c_status));
	}
	else
	{
		execve(path, args, environ);
	}
	if (WIFEXITED(c_status))
		return (WEXITSTATUS(c_status));
	return (0);
}
