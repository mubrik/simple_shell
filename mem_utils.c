#include "utils.h"

/**
	* _memcpy - copies the string pointed to by src,
	* including the terminating null byte (\0), to a malloc buffer
	* @src: buffer ptr
	* @dest: buffer ptr
	* Return: ptr to malloc'd string or null
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
