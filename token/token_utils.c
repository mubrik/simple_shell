#include "token.h"


/**
 * tokenize_args - splits a buffer of characters by a delimiter into a array
 * @input_b: argument count
 * @delim: delimiter
 * @argc: count
 * Return: a pointer to array of char*
 * Description: This mutates char **arg_list, not a pure function
 */
char **tokenize_args(char *input_b, char *delim, int argc)
{
	int i;
	char *token, *s, **arg_list;

	if (!input_b)
		return (NULL);

	arg_list = malloc(sizeof(char *) * argc);
	if (!arg_list)
		return (NULL);

	for (s = input_b, i = 0; ; s = NULL, i++)
	{
		token = strtok(s, delim);
		if (token)
			arg_list[i] = token, printf("Token not ull, i:%d argc: %d\n", i, argc);
		else
		{
			arg_list[i] = NULL;
			break;
		}
	}

	return (arg_list);
}

/**
 * tokenize_tl - splits buffer of chars to a token_list_t, malloc'd
 * @input_b: argument count
 * @delim: delimiter
 * @token_list: ptr to ptr of  type token_list_t
 * Return: char ** | NULL, list of tokens
 * Description: This mutates *token_list, not a pure function
 * it aso returns a malloc'd array, remeber to free
 */
char **tokenize_tl(char *input_b, char *delim, token_list_t **token_list)
{
	token_list_t *node = NULL, *iter = NULL;
	char *str, *token, **arr;
	size_t size, index;

	if (!input_b || !token_list)
		return (NULL);
	/* creat struct list */
	for (str = input_b, size = 0; ; str = NULL)
	{
		token = strtok(str, delim);
		if (!token)
			break;
		/* implement type/fleag checking for each token later */
		node = add_node_end(token_list, token, CMD_TOK), size++;
	}
	/* creat normal list */
	if (node)
	{
		arr = malloc(sizeof(char *) * (size + 1));
		if (!arr)
			return (NULL);
		/* check if start of list */
		while ((*token_list)->prev)
			*token_list = (*token_list)->prev;
		iter = *token_list;
		for (index = 0; index <= size; index++)
		{
			if (index == size)
			{
				arr[index] = NULL;
				continue;
			}
			arr[index] = iter->token;
			iter = iter->next;
		}

	}

	return (arr);
}

/**
 * add_node - adds a new node at the beginning of a token_list_t.
 * @head: ptr to head ptr to list first elem
 * @str: string pointer
 * @flag: flag type
 * Return: ptr to the new node.
 */
token_list_t *add_node(token_list_t **head, char *str, token_flag_t flag)
{
	token_list_t *node;

	/* alloc space */
	node = malloc(sizeof(token_list_t));
	if (!node)
		return (NULL);
	/* struct attribs */
	node->token = str, node->flag = flag, node->prev = NULL;
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
 * add_node_end - adds a new node at the end of a token_list_t.
 * @head: ptr to head ptr to list first elem
 * @str: string pointer
 * @flag: flag type
 * Return: ptr to the new node.
 */
token_list_t *add_node_end(token_list_t **head, char *str, token_flag_t flag)
{
	token_list_t *node, *curr_head;

	/* cp head */
	curr_head = *head;
	/* alloc space */
	node = malloc(sizeof(token_list_t));
	if (!node)
		return (NULL);
	/* struct attribs */
	node->token = str, node->flag = flag, node->next = NULL;
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
 * free_list- function that frees a token_list_t list.
 * @head: head ptr to list first elem
 * Return: void
 */
void free_list(token_list_t **head)
{
	token_list_t *tmp, *node;
	/* simple check */
	if (!head || !(*head))
		return;
	/* else iterate and free */
	node = *head;
	/* check if start of list */
	while (node->prev)
		node = node->prev;
	/* iterate foward from start */
	while (node)
	{
		/* cp the next ptr/null to tmp, free the current ptr memory */
		tmp = node->next, free(node), node = tmp;
	}
	/* final */
	*head = NULL;
}
