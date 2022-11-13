#include "which.h"

/**
 * tokenize_wl - splits a buffer of chars by a delimiter into a which_list_t
 * @input_b: buffer holding PATH values, will be mutated
 * @pathname: pathname
 * @delim: delimiter
 * @path_list: ptr to ptr of  type which_list
 * Return: which_list | NULL
 * Description: This mutates *path_list, not a pure function
 */
which_list_t *tokenize_wl(char *input_b, char *pathname,
	char *delim, which_list_t **path_list)
{
	which_list_t *node = NULL;
	char *str, *str_token, *f_path;
	struct stat f_info;

	if (!input_b || !path_list)
		return (NULL);

	for (str = input_b; ; str = NULL)
	{
		str_token = strtok(str, delim);
		if (!str_token)
			break;
		/* concat / then file name */
		f_path = _strconcatv(str_token, 2, "/", pathname);
		/* check if path + filename is correct */
		if (stat(f_path, &f_info) == -1)
			free(f_path); /* f_path is malloc'd */
		else
			node = add_node_end_wl(path_list, f_path);
	}

	return (node);
}

/**
 * add_node_wl - adds a new node at the beginning of a which_list_t.
 * @head: ptr to head ptr to list first elem
 * @str: string pointer
 * Return: ptr to the new node.
 */
which_list_t *add_node_wl(which_list_t **head, char *str)
{
	which_list_t *node;

	/* alloc space */
	node = malloc(sizeof(which_list_t));
	if (!node)
		return (NULL);
	/* struct attribs */
	node->path = str, node->prev = NULL;
	/* check if null, first node */
	if (*head)
	{
		/* check if start of list */
		while ((*head)->prev)
			*head = (*head)->prev;
		(*head)->prev = node;
	}
	/* set new node next to prev head, head to new nde */
	node->next = *head, *head = node;
	return (node);
}

/**
 * add_node_end_wl - adds a new node at the end of a which_list_t.
 * @head: ptr to head ptr to list first elem
 * @str: string pointer
 * Return: ptr to the new node.
 */
which_list_t *add_node_end_wl(which_list_t **head, char *str)
{
	which_list_t *node, *curr_head;

	/* cp head */
	curr_head = *head;
	/* alloc space */
	node = malloc(sizeof(which_list_t));
	if (!node)
		return (NULL);
	/* struct attribs */
	node->path = str, node->next = NULL;
	/* if null, first node */
	if (!curr_head)
		node->prev = NULL, *head = node;
	else
	{
		/* check if end of list */
		while (curr_head->next)
			curr_head = curr_head->next;
		/* assign next and prev to new node */
		node->prev = curr_head, curr_head->next = node;
	}
	return (node);
}

/**
 * free_list_wl- function that frees a which_list_t list.
 * @head: head ptr to list first elem
 * Return: void
 */
void free_list_wl(which_list_t *head)
{
	which_list_t *tmp, *node;
	/* simple check */
	if (!head)
		return;
	/* else iterate and free */
	node = head;
	/* check if start of list */
	while (node->prev)
		node = node->prev;
	/* iterate foward from start */
	while (node)
	{
		/* cp the next ptr/null to tmp, free the current ptr memory */
		tmp = node->next, free(node->path), free(node), node = tmp;
	}
	/* final */
	/* head = NULL; */
}
