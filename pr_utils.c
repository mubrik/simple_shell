#include "shell.h"

/**
 * _print - does printf stuff
 * @string: stirng format of string
 * @fd: stdin or stderr
 * Return: number of bytes printed or -1 for fail
 * Description: cant use variadic function, dumb limitation
 */
int _print(const char *string, int fd)
{
	char *buffer;
	int count = 0, buffer_i = 0;

	if (!string || !fd)
		return (-1);
	/* alloc */
	buffer = malloc(P_BUFF_SIZE);
	if (!buffer)
		return (-1);
	/* simple iteration */
	while (string[count])
		add_to_buffer(fd, string[count], buffer, &buffer_i), count++;
	/* print last buffer */
	print_buffer(fd, buffer, buffer_i);
	/* free */
	free(buffer);
	return (count);
}

/**
 * _print_num - does prints numbers
 * @num: num to print
 * @fd: stdin or stderr
 * Return: number
 */
int _print_num(int num, int fd)
{
	char *buffer;
	int count = 0, buffer_i = 0;
	unsigned int div_by = 1;

	if (!fd)
		return (-1);
	/* alloc */
	buffer = malloc(P_BUFF_SIZE);
	if (!buffer)
		return (-1);
	if (num < 0) /* neg sign */
	{
		add_to_buffer(fd, '-', buffer, &buffer_i);
		num = num * -1;
	}
	/* div and prin remainder */
	while ((num / div_by) > 9)
		div_by *= 10;
	while (div_by > 0)
	{
		add_to_buffer(fd, ((num / div_by) % 10) + '0', buffer, &buffer_i);
		count++, div_by /= 10;
	}

	/* print last buffer */
	print_buffer(fd, buffer, buffer_i);
	/* free */
	free(buffer);
	return (count);
}

/**
 * _print_err - wrapper to print error easily
 * @shell_d: shell data
 * @cmd: cmd_prop_t
 * @err: err string
 * Return: number
 */
int _print_err(shell_data_t *shell_d, cmd_prop_t *cmd, char *err)
{
	if (!shell_d || !cmd)
		return (0);
	/* print program name */
	_print(shell_d->shell_argv[0], STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	/* print line number */
	_print_num(shell_d->cmd_num, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	/* print cmd with err */
	_print(cmd->argv[0], STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	/* print string */
	if (err)
		_print(err, STDERR_FILENO);
	return (0);
}


/**
 * print_buffer - writes bytes of a buffer to stdout
 * @fd: stdin or stdout
 * @buffer: the ptr to a buffer
 * @byte_count: number of byte to write
 * Return: the next available index int
 */
int print_buffer(int fd, char *buffer, int byte_count)
{
	return (write(fd, buffer, byte_count));
}

/**
 * add_to_buffer - adds a charatcter to index of a buffer
 * @fd: stdin or stdout
 * @str: the character
 * @buffer: the ptr to a buffer
 * @buffer_i: index of buffer
 * Return: the next available index int
 */
int add_to_buffer(int fd, char str, char *buffer, int *buffer_i)
{
	if (*buffer_i >= P_BUFF_SIZE)
	{
		/* flush/print out the buffer */
		print_buffer(fd, buffer, P_BUFF_SIZE);
		/* set index to start */
		*buffer_i = 0;
	}
	/* add chr to buffer and incr index */
	buffer[*buffer_i] = str, *buffer_i += 1;
	return (*buffer_i);
}
