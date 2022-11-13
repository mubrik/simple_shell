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
