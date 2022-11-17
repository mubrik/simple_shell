#include "which.h"

/**
 * is_path - checks if string is a pathname
 * @s: ponter t string
 * Return: int
 */
static inline int is_path(char *s) { return ((s[0] == '.') || (s[0] == '/')); }

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
	{
		if (stat(command, &f_info) == 0)
		{
			/* confirm its a file not directory */
			if ((f_info.st_mode & S_IFMT) == S_IFREG)
				f_path = _strdup(command); /* dup cause free after */
		}
	}
	else
	{
		path = _strdup(_getenv("PATH")); /* dup cause tokenization cuts orig */
		if (!path)
			return (NULL);
		for (str = path; ; str = NULL)
		{
			pathname = _strtok(str, ":");
			if (!pathname)
				break;
			/* concat '/' then command */
			f_path = _strconcatd(pathname, "/", command);
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
	}

	if (path)
		free(path);
	return (f_path);
}
