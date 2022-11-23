#include "utils.h"

/**
	* _memcpy - copies the contents of a ptr to another buffer
	* @src: buffer ptr
	* @dest: buffer ptr
	* Return: int 1 if successful
	*/
int _memcpy(const char *src, char *dest)
{
	int index = 0;

	if (!src || !dest)
		return (0);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}

	return (1);
}

/**
	* _str_realloc - specific function for realloc a string buffer
	* this frees up the previous buffer!
	* @src: buffer ptr
	* @buf_size: size of new mem
	* @size_n: size of new mem
	* Return: ptr to malloc'd string or null
	*/
char *_str_realloc(char *src, size_t buf_size, size_t size_n)
{
	char *new_buf;

	if (!src)
		return (src);

	if (size_n < buf_size)
		return (src);
	/* alloc */
	new_buf = malloc(sizeof(char) * size_n);
	if (!new_buf)
		return (NULL);
	/* copy old to new, free previous */
	_strncpy(src, new_buf, buf_size), free(src);
	return (new_buf);
}

/**
	* lst_size - gets the size of a list
	* @arr: buffer ptr
	* Return: -1 on error, size in int
	*/
int lst_size(char **arr)
{
	int index = 0;

	if (!arr)
		return (-1);
	while (arr[index])
		index++;

	return (index);
}

/**
	* free_lst - frees a list of malloc'd pointers
	* @arr: buffer ptr
	* Return: -1 on error, size in int
	*/
int free_lst(char **arr)
{
	int index = 0;

	if (!arr)
		return (-1);
	while (arr[index])
		free(arr[index]), index++;

	return (index);
}
