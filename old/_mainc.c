#include "main.h"

/**
 * read_inputv - prits a '$' to the terminal and store line into the buffer
 * @fd: file descriptor to read from
 * @buffer: buffer to tore string
 * @n_bytes: ptr to number of bytes written
 * Return: int, number of bytes stored
 */
ssize_t read_inputv(int fd, char **buffer, size_t n_bytes)
{
	ssize_t byte_r, total_r = 0;
	buf tmp;
	/* write $ */
	fflush(stdout), fflush(stderr);
	if (isatty(STDIN_FILENO)) /* real interactive mode check */
		write(1, "#cisfun$ ", 9);
	while ((byte_r = read(fd, (*buffer + total_r), n_bytes)) >= IN_BUFF_SIZE)
	{
		total_r += byte_r;
		tmp = _str_realloc(*buffer, total_r, total_r + IN_BUFF_SIZE);
		if (!tmp)
		{
			total_r -= byte_r;
			break;
		}
		*buffer = tmp;
		if (byte_r == IN_BUFF_SIZE && ((*buffer)[total_r - 1] == '\n'))
		{
			byte_r = 0;
			break;
		}
	}
	total_r += byte_r;

	if (total_r <= 0) /* 0 == EOF */
	{
		/* frreing not necessary as app is exiting but doing it anyways */
		if (is_env_change(0))
			free_lst(environ), free(environ);
		free(*buffer), *buffer = NULL;
		return (-1);
	}
	(*buffer)[total_r] = '\0';
	return (total_r);
}
