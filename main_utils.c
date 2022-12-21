#include "shell.h"

/**
 * init_shell_data - initializes shell data
 * @argc: argument count
 * @argv: array of char argument values
 * @fd: file descriptor
 * @shell_d: pointer to shell data
 * Return: 0 if success, -1 else
 */
int init_shell_data(int argc, char **argv, int fd, shell_data_t *shell_d)
{
	buf input_b, *p_arr;

	if (!shell_d)
		return (-1);
	/* set argc and argv */
	shell_d->shell_argc = argc, shell_d->shell_argv = argv;
	/* set interactive */
	shell_d->i_mode = isatty(fd);
	/* exit code and pid  */
	shell_d->exit_code = 0, shell_d->s_pid = getpid();
	/* cmd num */
	shell_d->cmd_num = 1;
	/* input buffer */
	input_b = malloc(sizeof(char) * (IN_BUFF_SIZE + 1));
	if (!input_b)
		return (-1);
	shell_d->input_buff = input_b;
	/* head for command list */
	shell_d->cmd_list = NULL;
	/* alias */
	shell_d->alias_head = NULL;
	/* ponters arr */
	p_arr = malloc(sizeof(buf) * (P_AR + 1));
	if (!p_arr)
		return (-1);
	/* set first item to null and assign */
	p_arr[0] = NULL, shell_d->p_arr = p_arr;
	return (0);
}

/**
 * process_data - prepares the necessary data to be used
 * @shell_d: pointer to shell data
 * Return: 0 if success, -1 else
 */
int process_data(shell_data_t *shell_d)
{
	int result = 0;
	/* tokenize the input buffer by |&;\n delim ->  cmd_prop_t list */
	result = inp_tok(shell_d->input_buff, &(shell_d->cmd_list));
	if (result != 0 || !shell_d->cmd_list)
		return (result);
	/* add args list by tokenize each comand " " delim in a cmd_prop_t list */
	result = cmd_to_args(shell_d);

	return (result);
}

/**
 * ref_shell_data - refreshes shell data after op's for interactve mode
 * @shell_d: pointer to shell data
 * Return: 0 if success, -1 else
 */
int ref_shell_data(shell_data_t *shell_d)
{
	cmd_prop_t *tmp;

	if (!shell_d)
		return (0);
	if (!shell_d->cmd_list)
		return (0);
	/* free up arg_list in command list */
	tmp = shell_d->cmd_list;
	while (tmp)
	{
		if (tmp->argv)
			free(tmp->argv);
		tmp = tmp->next;
	}
	/* free up cmd_list */
	free_cmdlist(shell_d->cmd_list), shell_d->cmd_list = NULL;
	return (0);
}

/**
 * free_shell_data - free malloc data in shell_d
 * @shell_d: pointer to shell data
 * Return: 0 if success, -1 else
 */
int free_shell_data(shell_data_t *shell_d)
{
	int i = 0;

	if (!shell_d)
		return (0);
	/* free input buffer */
	if (shell_d->input_buff)
		free(shell_d->input_buff), shell_d->input_buff = NULL;
	/* free cmd linked list */
	if (shell_d->cmd_list)
		/* free up arg_list in command list */
		ref_shell_data(shell_d);
	/* alias list */
	if (shell_d->alias_head)
		free_aliaslist(shell_d->alias_head), shell_d->alias_head = NULL;
	/* environmnet variables */
	if (is_env_change(0))
		free_lst(environ), free(environ);
	/* free up dangling ptrs */
	while (shell_d->p_arr[i] && i < P_AR)
		/* if any index is NULL, rest null */
		free(shell_d->p_arr[i]), i++;
	free(shell_d->p_arr);
	return (0);
}

/**
 * get_input - prits a '$' to the terminal and store line into the buffer
 * @fd: file descriptor to read from
 * @shell_d: pointer to shel data
 * Return: int, number of bytes stored
 */
ssize_t get_input(int fd, shell_data_t *shell_d)
{
	ssize_t byte_r, total_r = 0;
	buf tmp = NULL, main_buff = NULL;

	if (!shell_d)
		return (-1);
	/* copy buffer ptr, flush outputs */
	main_buff = shell_d->input_buff, fflush(stdout), fflush(stderr);
	/* write $ */
	if (shell_d->i_mode)
		write(1, "#cisfun$ ", 9);
	/* while loop to reallocate if iput larger than buffer */
	while ((byte_r = read(fd,
		(main_buff + total_r), IN_BUFF_SIZE)) >= IN_BUFF_SIZE)
	{
		total_r += byte_r; /* realloc, str_re frees up previous buff */
		tmp = _str_realloc(main_buff, total_r, total_r + IN_BUFF_SIZE);
		if (!tmp)
		{
			total_r -= byte_r;
			break;
		}
		main_buff = shell_d->input_buff = tmp; /* re assign new ptr */
		if (byte_r == IN_BUFF_SIZE && ((main_buff)[total_r - 1] == '\n'))
		{
			byte_r = 0;
			break;
		}
	}
	total_r += byte_r;

	if (total_r <= 0) /* 0 == EOF */
	{
		free_shell_data(shell_d);
		return (-1);
	}
	(main_buff)[total_r] = '\0';
	_str_comment(shell_d); /* strip comments */
	return (total_r);
}
