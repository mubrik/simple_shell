#include "which.h"

/**
 * _getenv - gets a variable from environment
 * @name: name of variable
 * Return: string of env variable or NULL
 */
char *_getenv(char *name)
{
	int i, j;

	if (!name)
		return (NULL);
	/* iterate ovver env variables */
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		/* iterate over name */
		while (name[j])
		{
			/* immediately break if no match */
			if (name[j] != environ[i][j])
				break;
			/* if next is null, and next in env variable is '=' */
			if (name[j + 1] == '\0' && environ[i][j + 1] == '=')
				return (&environ[i][j + 2]);
			j++;
		}
	}

	return (NULL);
}

/**
 * _which - takes a pathname and sets a which_list_t
 * @pathname: ptr to name of file
 * Return: a which_list_t or NULL if not found
 */
which_list_t *_which(char *pathname)
{
	char *path = NULL;
	which_list_t *path_list = NULL;
	/* struct stat f_info; */

	if (!pathname)
		return (NULL);
	/* verify pathname */
	printf("Which called with %s\n", pathname);
	if (is_path(pathname))
		add_node_end_wl(&path_list, _strdup(pathname)); /* printf("valid"); */
	else
	{
		path = _strdup(_getenv("PATH")); /* dup cause tokenization cuts orig */
		if (!path)
			return (NULL);
		/* tokenize */
		tokenize_wl(path, pathname, ":", &path_list);
	}

	/* return early if a path bt invalid */

	/* if not path, check PATH */
	if (path)
		free(path);
	return (path_list);
}
