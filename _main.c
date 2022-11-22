#include "main.h"

/**
 * read_input - prits a '$' to the terminal and stores the line into the buffer
 * @fd: file descriptor to read from
 * @buffer: buffer to tore string
 * @n_bytes: ptr to number of bytes written
 * Return: int, number of bytes stored
 */
ssize_t read_input(int fd, char **buffer, size_t *n_bytes)
{
	int byte_r;
	/* write $ */
	fflush(stdout), fflush(stderr);
	if (isatty(STDIN_FILENO)) /* real interactive mode check */
		write(1, "#cisfun$ ", 9);
	byte_r = read(fd, *buffer, *n_bytes);
	/* byte_r = getline(buffer, n_bytes, stdin); */
	if (byte_r <= 0) /* 0 == EOF */
	{
		/* frreing not necessary as app is exiting but doing it anyways */
		if (is_env_change(0))
			free_lst(environ), free(environ);
		free(*buffer);
		return (-1);
	}
	(*buffer)[byte_r] = '\0';
	return (byte_r);
}

/**
 * set_buffers - alloc default space required for buffers
 * @input_b: argument count
 * Return: 1 if buffesr set, 0 otherwise
 */
int set_buffers(char **input_b)
{
	*input_b = malloc(IN_BUFF_SIZE);
	if (!(*input_b))
		return (0);
	return (1);
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

	return (0);
}

/**
 * main - main function int argc, char *argv[]
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int main(__attribute__((unused)) int argc, char *argv[])
{
	int n_read, i_argc = 0, ex_code = 0, cmd_exec = 0;
	buf inp_b = NULL, *arg_list = NULL, tmp_b = NULL, cmd_b = NULL, tok_r = NULL;
	u_long inp_bytes = IN_BUFF_SIZE;
	token_list_t *token_list = NULL;
	/* non interactive mode */
	if (!set_buffers(&inp_b)) /* interactive */ /* chck */
		return (-1);
	while ((n_read = read_input(STDIN_FILENO, &inp_b, &inp_bytes)) != -1)
	{
		for (tmp_b = inp_b; ; tmp_b = NULL)
		{
			cmd_b = _strtok_r(tmp_b, "\n;", &tok_r);
			if (cmd_b && (ex_code == 0))
			{
				arg_list = tokenize_tl(cmd_b, " \t", &token_list, &i_argc), cmd_exec++;
				ex_code = handle_cmd_type(i_argc, arg_list);
				handle_p_exit(ex_code, argv[0], i_argc, arg_list), free(arg_list);
			}
			else
				break;
		}
		if (!isatty(STDIN_FILENO)) /* non interactive mode check */
			break;
		ex_code = 0; /* going again, reset ex_code */
	}
	if (inp_b)
		free(inp_b);
	return (ex_code);
}

/**
 * handle_cmd_type - a sub function to reduce main function line count
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int handle_cmd_type(int argc, char **argv)
{
	if (!argv)
		return (0);

	if (is_builtin(argv[0]))
		return (handle_bin(argc, argv));
	else
		return (handle_ext(argc, argv));
}
