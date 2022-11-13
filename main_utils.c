#include "main.h"

/**
 * filter_argv - filters out he progrma name from argv into a new buffer
 * @argv: argv buffer
 * @argc: argument count
 * Return: a pointer to array of char*
 */
char **filter_argv(char **argv, int argc)
{
	int i;
	char **arr;

	if (!argc || !argv)
		return (NULL);

	arr = malloc(sizeof(char *) * argc);
	if (!arr)
		return (NULL);

	for (i = 0; i <= argc; i++)
	{
		if (i == 0) /* skip program name */
			continue;
		if (i == argc)
		{ /* add last null and break loop */
			arr[i - 1] = NULL;
			break;
		}
		arr[i - 1] = argv[i];
	}

	return (arr);
}
