#include "shell.h"

/**
 * add_node_argl_end - adds a new node at the end of a arg_list_t.
 * @head: ptr to head ptr to list first elem
 * @str: string pointer
 * Return: ptr to the new node.
 */
arg_list_t *add_node_argl_end(arg_list_t **head, char *str)
{
	arg_list_t *node = NULL, *tmp = NULL;
	/* null chk */
	if (!head)
		return (NULL);
	/* alloc space */
	node = malloc(sizeof(arg_list_t));
	if (!node)
		return (NULL);
	/* get last node */
	if (*head)
	{
		tmp = *head;
		while (tmp)
		{
			if (!tmp->next)
				break;
			tmp = tmp->next;
		}
		/* point last node next to new node */
		tmp->next = node;
	}
	else
		*head = node;
	/* struct attribs, make new node prev last */
	node->token = str, node->prev = tmp, node->next = NULL;

	return (node);
}

/**
 * free_arg_list- function that frees a arg_list_t list.
 * @head: head ptr to list first elem
 * Return: void
 */
void free_arg_list(arg_list_t *head)
{
	arg_list_t *next;

	if (!head)
		return;
	/* make sure start of node*/
	while (head)
	{
		if (!head->prev)
			break;
		head = head->prev;
	}
	/* iterate foward and free */
	while (head)
		next = head->next, free(head), head = next;
}

/**
 * arg_tok - splits buffer of chars to a list, malloc'd
 * @input_b: argument count
 * @delim: delimiter
 * @l_size: ptr size of list
 * Return: char ** | NULL, list of tokens
 * Description: it returns a malloc'd array, remeber to free
 */
char **arg_tok(char *input_b, char *delim, int *l_size)
{
	arg_list_t *node = NULL, *iter = NULL, *head = NULL;
	char *str = NULL, *token = NULL, **arr = NULL;
	size_t size = 0, index;

	if (!input_b)
		return (NULL);
	/* creat struct list */
	for (str = input_b, size = 0; ; str = NULL)
	{
		token = _strtok(str, delim);
		if (!token)
			break;
		node = add_node_argl_end(&head, token), size++;
	}
	/* creat normal list */
	if (node)
	{
		arr = malloc(sizeof(char *) * (size + 1));
		if (!arr)
			return (NULL);
		/* check if start of list */
		while (head->prev)
			head = head->prev;
		iter = head; /* copy head to mutate in loop */
		for (index = 0; index <= size; index++)
		{
			if (index == size)
			{
				arr[index] = NULL;
				continue;
			}
			arr[index] = iter->token, iter = iter->next;
		}
		/* free */
		free_arg_list(head);
	}
	/* update list size, free */
	*l_size = size;

	return (arr);
}

/**
 * cmd_to_args - mutate a cmd_prop_t list, add malloc'd args list and arg count
 * @cmd_list: head
 * Return: 0 on success
 */
int cmd_to_args(cmd_prop_t *cmd_list)
{
	cmd_prop_t *tmp = NULL;
	char **arg_list = NULL;
	int list_s = 0;

	if (!cmd_list)
		return (-1);
	tmp = cmd_list;
	while (tmp)
	{
		arg_list = arg_tok(tmp->cmd, " \t", &list_s);
		if (arg_list)
			tmp->argv = arg_list, tmp->argc = list_s;
		else
			tmp->argv = NULL, tmp->argc = 0;
		tmp = tmp->next;
	}

	return (0);
}

/**
 * print_args_cmdlist - debug, print args
 * @cmd_list: head
 * Return: 0 on success
 */
int print_args_cmdlist(cmd_prop_t *cmd_list)
{
	int i = 0;

	if (!cmd_list)
		return (1);
	/* iterate over each commd */
	while (cmd_list)
	{
		for (i = 0; cmd_list->argv[i]; i++)
		{
			_print(cmd_list->argv[i], STDOUT_FILENO);
		}
		_print("\n", STDOUT_FILENO);
		cmd_list = cmd_list->next;
	}
	return (i);
}
