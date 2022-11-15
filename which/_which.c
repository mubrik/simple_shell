#include "which.h"

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
		return (path_list);
	/* verify pathname */
	if (is_path(pathname))
		add_node_end_wl(&path_list, _strdup(pathname)), printf("valid");
	else
	{
		path = _strdup(_getenv("PATH")); /* dup cause tokenization cuts orig */
		if (!path)
			return (NULL);
		/* tokenize */
		tokenize_wl(path, pathname, ":", &path_list);
	}

	if (path)
		free(path);
	return (path_list);
}
