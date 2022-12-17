#include "shell.h"

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
