#include "./which/which.h"

/**
 * _which - find the first valid command path, mallocd
 * @command: user command to find
 * Return: valid pathname or NULL
 */
char *_which(char *command)
{
	char *path = NULL, *pathname = NULL, *str = NULL, *f_path = NULL;
	struct stat f_info;

	if (!command)
		return (NULL);
	/* verify cmd is pathname */
	if (is_path(command))
		return (command);
	path = _strdup(_getenv("PATH")); /* dup cause tokenization cuts orig */
	if (!path)
		return (NULL);
	for (str = path; ; str = NULL)
	{
		pathname = _strtok(str, ":");
		if (!pathname)
			break;
		/* concat '/' then command */
		f_path = _strconcatv(pathname, 2, "/", command);
		/* check if path + cmd is correct */
		if (stat(f_path, &f_info) == -1)
			free(f_path), f_path = NULL; /* f_path is malloc'd */
		else
		{
			/* valid path found */
			free(path);
			return (f_path);
		}
	}

	if (path)
		free(path);
	return (f_path);
}
