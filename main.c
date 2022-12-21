#include "shell.h"

/**
 * main - main function int argc, char *argv[]
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int main(int argc, char *argv[])
{
	int n_read, ex_code = 0, fd = STDIN_FILENO;
	shell_data_t shell_data;

	if (argc == 2)
	{
		/* too gaudy, adjust later */
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			_print(argv[0], STDERR_FILENO);
			_print(": 0: Can't open ", STDERR_FILENO);
			_print(argv[1], STDERR_FILENO), _print("\n", STDERR_FILENO);
			return (CNF);
		}
	}
	/* initialize shell data */
	if (init_shell_data(argc, argv, fd, &shell_data) != 0)
		return (-1);
	while ((n_read = get_input(fd, &shell_data)) != -1)
	{
		/* main program loop */
		process_data(&shell_data);
		ex_code = process_cmds(&shell_data);
		ref_shell_data(&shell_data);
	}
	if (shell_data.input_buff)
		free(shell_data.input_buff);

	return (ex_code);
}
