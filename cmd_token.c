#include "shell.h"

/**
 * add_node_cmd_end - adds a new node at the end of a cmd_prop_t list.
 * @head: pto to head ptr to list first elem
 * @buf: str to add
 * @n: n for new node
 * Return: ptr to new node.
 */
cmd_prop_t *add_node_cmd_end(cmd_prop_t **head, char *buf, int n)
{
	cmd_prop_t *node = NULL, *tmp = NULL;
	/* null chk */
	if (!head)
		return (NULL);
	/* alloc space */
	node = malloc(sizeof(cmd_prop_t));
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
	node->flag = n, node->cmd = buf, node->argc = 0, node->argv = NULL;
	node->prev = tmp, node->next = NULL;

	return (node);
}

/**
 * cmdlist_len - gets size of a cmd_prop_t list..
 * @head: head ptr to list first elem
 * Return: list size .
 */
size_t cmdlist_len(const cmd_prop_t *head)
{
	size_t count = 0;
	cmd_prop_t *node;

	/* cp first ptr, cast to remove const */
	node = (cmd_prop_t *) head;

	/* make sure start of node, not necessary but alx gon alx */
	while (node)
	{
		if (!node->prev)
			break;
		node = node->prev;
	}
	/* iterate */
	while (node)
		node = node->next, count++;

	return (count);
}

/**
 * print_cmdlist - prints all the elements of a cmd_prop_t list..
 * @head: head ptr to list first elem
 * Return: list size .
 */
size_t print_cmdlist(const cmd_prop_t *head)
{
	size_t count = 0;
	cmd_prop_t *node;

	/* cp first ptr, cast to remove const */
	node = (cmd_prop_t *) head;
	/* make sure start of node, not necessary but alx gon alx */
	while (node)
	{
		if (!node->prev)
			break;
		node = node->prev;
	}

	/* iterate */
	while (node)
	{
		printf("cmd: %s, flag: %d\n", node->cmd, node->flag);
		/* push */
		node = node->next, count++;
	}

	return (count);
}

/**
 * free_cmdlist - frees memory of cmd_prop_t list.
 * @head: pto to head ptr to list first elem
 * Return: ptr to new node.
 */
void free_cmdlist(cmd_prop_t *head)
{
	cmd_prop_t *next;

	if (!head)
		return;
	/* make sure start of node, not necessary but alx gon alx */
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
 * inp_tok - tokenize the string from input buffer
 * @buffer: input buffer ptr
 * @head: head to doubly linked list cmd_prop_t
 * Return: 0 if success, 1 else
 */
int inp_tok(char *buffer, cmd_prop_t **head)
{
	int i, first_f = 0, run_mode = CMD_NL;
	char *str_chk, *start = NULL, *delim = ";|&\n";

	if (!buffer)
		return (-1);
	for (i = 0; buffer[i]; i++)
	{
		str_chk = _strchr(delim, buffer[i]);
		if (!first_f && !str_chk) /* first char that isnt delim */
			start = &buffer[i], first_f = 1;
		if (first_f && str_chk) /* have a first char and found delim */
		{
			buffer[i] = '\0'; /* terminate and add node to linked list */
			add_node_cmd_end(head, start, run_mode);
			/* change next command mode based on delim */
			if (*str_chk == '&')
				run_mode = CMD_AND;
			else if (*str_chk == '\n' || *str_chk == ';')
				run_mode = CMD_NL;
			else
				run_mode = CMD_OR;
			/* reset first */
			first_f = 0;
		}
		else if (first_f && buffer[i + 1] == '\0')
			add_node_cmd_end(head, start, run_mode);
	}

	return (0);
}
