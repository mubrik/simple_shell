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
	int n_read, __attribute_maybe_unused__ mode;
	/* buffers */
	buf inp_b = NULL, *arg_list = NULL;
	u_long inp_bytes = IN_BUFF_SIZE;
	token_list_t *token_list = NULL;
	which_list_t *path_list = NULL;
	/* non interactive mode */
	if (argc > 1)
	{
		mode = NONINT, arg_list = filter_argv(argv, argc);
		if (!arg_list)
			return (-1);
		printf("Arg count %d\n, first Arg: %s\n", argc, arg_list[1]);
		path_list = _which(arg_list[1]);
		if (!path_list)
			perror(arg_list[0]), perror(": No such file or directory");
		else
			exec_cmd(path_list->path, arg_list, env), free_list_wl(path_list);
	}
	else /* interactive */
	{
		if (!set_buffers(&inp_b)) /* chck */
			return (-1);
		while ((n_read = get_input(inp_b, &inp_bytes)) != -1)
		{
			mode = INT, printf("buffer %s\n", inp_b);
			arg_list = tokenize_tl(inp_b, " \n", &token_list);
			if (arg_list)
			{
				path_list = _which(arg_list[0]);
				if (!path_list)
					perror("No such file or directory");
				else
					exec_cmd(path_list->path, arg_list, env), free_list_wl(path_list);
				free_list(&token_list), free(arg_list);
			}
		}
		free(inp_b);
	}
	return (0);
}
