#include "./utils/utils.h"

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
