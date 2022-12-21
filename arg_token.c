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
 * @shell_d: ptr to shell_data
 * Return: 0 on success
 */
int cmd_to_args(shell_data_t *shell_d)
{
	cmd_prop_t *tmp = NULL;
	char **arg_list = NULL;
	int list_s = 0;

	if (!shell_d || !shell_d->cmd_list)
		return (-1);
	tmp = shell_d->cmd_list;
	while (tmp)
	{
		/* tokenize strings in cmd_list_t into normal array */
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
 * var_substitute - substitues arg like $? $$
 * @shell_d: ptr to shell_data
 * @argv: head
 * @argc: head
 * Return: 0 on success
 */
int var_substitute(shell_data_t *shell_d, char **argv, int argc)
{
	int index, count = 0;
	buf val = NULL, env = NULL, new = NULL;
	char buff[50] = { '\0' };

	if (!shell_d || !argv)
		return (1);
	if (argc == 0)
		return (0);
	/* iterate over arr */
	for (index = 0; index < argc; index++)
	{
		val = argv[index];
		if (!val)
			continue;
		if (_strcmp(val, "$?") == 0)
		{
			/* get ex code and replace value */
			new = _strdup(_itoa(shell_d->exit_code, buff, 10));
			/* str ptrs */ /* limit of 50, make this comprehensive later */
			add_to_p_arr(shell_d, new), argv[index] = new, count++;
			continue;
		}

		if (_strcmp(val, "$$") == 0)
		{
			/* replace with shell pid */
			new = _strdup(_itoa(shell_d->s_pid, buff, 10));
			add_to_p_arr(shell_d, new), argv[index] = new, count++;
			continue;
		}

		if (val[0] == '$' && val[1])
		{
			/* replace with env var */
			env = _getenv(val + 1), argv[index] = env, count++;
			continue;
		}
	}
	return (count);
}
