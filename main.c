#include "shell.h"

/**
 * main - main function int argc, char *argv[]
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int main(int argc, char *argv[])
{
	int n_read, ex_code = 0;
	shell_data_t shell_data;

	if (init_shell_data(argc, argv, &shell_data) != 0)
		return (-1);
	while ((n_read = get_input(STDIN_FILENO, &shell_data)) != -1)
	{
		process_data(&shell_data);
		/* printf("Bufer: %s \n", shell_data.input_buff); */
		/* print_cmdlist(shell_data.cmd_list); */
		ex_code = process_cmds(&shell_data);
		/* printf("Exit code %d \n", ex_code); */
		ref_shell_data(&shell_data);
		/* inp_tok(shell_data.input_buff, &(shell_data.cmd_list)); */
		/* free_cmdlist(shell_data.cmd_list), shell_data.cmd_list = NULL; */
	}
	if (shell_data.input_buff)
		free(shell_data.input_buff);

	return (ex_code);
}
