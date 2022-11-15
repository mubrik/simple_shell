#include "main.h"

/**
 * get_input - prits a '$' to the terminal and stores the line into the buffer
 * @buffer: buffer to tore string
 * @n_bytes: ptr to number of bytes written
 * Return: int, number of bytes stored
 */
ssize_t get_input(char *buffer, u_long *n_bytes)
{
	/* write $ */
	write(1, "$ ", 2);
	return (getline(&buffer, n_bytes, stdin));
}

/**
 * read_input - prits a '$' to the terminal and stores the line into the buffer
 * @fd: file descriptor to read from
 * @buffer: buffer to tore string
 * @n_bytes: ptr to number of bytes written
 * Return: int, number of bytes stored
 */
ssize_t read_input(int fd, char *buffer, size_t n_bytes)
{
	int byte_r;

	/* write $ */
	write(1, "$ ", 2);
	byte_r = read(fd, buffer, n_bytes);
	if (byte_r <= 0) /* 0 == EOF */
		return (-1);
	buffer[byte_r] = '\0';
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
 * @env: array of char environment variables
 * Return: int
 */
int exec_cmd(char *path, char **args, char **env)
{
	int c_pid, c_status;
	/* check */
	if (!path || !args || !env)
	{
		return (-1);
	}
	c_pid = fork();
	if (c_pid == -1)
		printf("error executing");
	else if (c_pid > 0)
	{
		printf("waiting \n");
		wait(&c_status);
		printf("done waiting \n");
		return (0);
	}
	else
	{
		execve(path, args, env);
		/* printf("Path to execv: %s\n", path_list->path); */
	}

	return (0);
}

/**
 * main - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: int
 */
int main(int argc, char *argv[], char *env[])
{
	int n_read, i_argc = 0, ex_code = 0;
	/* buffers */
	buf inp_b = NULL, *arg_list = NULL;
	u_long inp_bytes = IN_BUFF_SIZE;
	token_list_t *token_list = NULL;
	/* non interactive mode */
	if (argc > 1)
	{
		arg_list = filter_argv(argv, argc);
		if (!arg_list)
			return (-1);
		if (is_builtin(arg_list[0]))
			ex_code = handle_bin(argc - 1, &arg_list, env);
		else
			ex_code = handle_ext(argc - 1, &arg_list, env);
		handle_p_exit(ex_code, argv[0], argc - 1, arg_list, env), free(arg_list);
		return (0);
	}
	/* interactive */
	if (!set_buffers(&inp_b)) /* chck */
		return (-1);
	while ((n_read = read_input(STDIN_FILENO, inp_b, inp_bytes)) != -1)
	{
		printf("buffer %s\n", inp_b);
		arg_list = tokenize_tl(inp_b, " \n", &token_list, &i_argc);
		if (arg_list)
		{
			printf("first arg %s\n", arg_list[0]);
			if (is_builtin(arg_list[0]))
				ex_code = handle_bin(i_argc, &arg_list, env);
			else
				ex_code = handle_ext(i_argc, &arg_list, env);
			handle_p_exit(ex_code, argv[0], i_argc, arg_list, env), free(arg_list);
		}
	}
	free(inp_b);
	return (ex_code);
}
