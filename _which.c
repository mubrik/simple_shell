#include "shell.h"

/**
 * _which - find the first valid command path, mallocd
 * @command: user command to find
 * Return: valid pathname or NULL
 */
char *_which(char *command)
{
	buf path = NULL, pathname = NULL, str = NULL, f_path = NULL, tmp = NULL;
	struct stat f_info;

	if (!command)
		return (NULL);
	/* verify cmd is pathname */
	if (is_path(command))
	{
		if (stat(command, &f_info) == 0)
		{
			if ((f_info.st_mode & S_IFMT) == S_IFREG) /* confirm file not dir */
				f_path = _strdup(command); /* dup cause free after */
		}
	}
	else
	{
		tmp = _getenv("PATH");
		if (!tmp)
			return (tmp);
		path = _strdup(tmp); /* dup cause tokenization cuts orig */
		if (!path)
			return (NULL);
		for (str = path; ; str = NULL)
		{
			pathname = _strtok(str, ":");
			if (!pathname)
				break;
			f_path = _strconcatd(pathname, "/", command); /* concat '/' then command */
			if (stat(f_path, &f_info) == -1) /* check if path + cmd is correct */
				free(f_path), f_path = NULL; /* f_path is malloc'd */
			else
			{
				free(path); /* valid path found */
				return (f_path);
			}
		}
	}
	if (path)
		free(path);
	return (f_path);
}
