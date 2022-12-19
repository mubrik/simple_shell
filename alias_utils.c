#include "shell.h"

/**
 * add_node_alias_end - adds a new node at the end of a alias_d_t list.
 * @head: pto to head ptr to list first elem
 * @name: name of alis
 * @value: value of alias
 * Return: ptr to new node.
 */
alias_d_t *add_node_alias_end(alias_d_t **head, char *name, char *value)
{
	alias_d_t *node = NULL, *tmp = NULL;
	/* null chk */
	if (!head)
		return (NULL);
	/* alloc space */
	node = malloc(sizeof(alias_d_t));
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
	node->name = _strdup(name), node->value = _strdup(value);
	node->prev = tmp, node->next = NULL;

	return (node);
}

/**
 * aliaslist_len - gets size of a alias_d_t list..
 * @head: head ptr to list first elem
 * Return: list size .
 */
size_t aliaslist_len(const alias_d_t *head)
{
	size_t count = 0;
	alias_d_t *node;

	/* cp first ptr, cast to remove const */
	node = (alias_d_t *) head;

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
 * print_aliaslist - prints all the elements of a alias_d_t list..
 * @head: head ptr to list first elem
 * @cmp: str to cmp to, if NULl cmp wont be done
 * Return: list size .
 */
size_t print_aliaslist(alias_d_t *head, char *cmp)
{
	size_t count = 0;
	alias_d_t *node = NULL;

	if (!head)
		return (count);
	/* cp first ptr */
	node = head;
	/* make sure start of node, not necessary but alx gon alx */
	while (node)
	{
		if (!node->prev)
			break;
		node = node->prev;
	}

	/* iterate */
	for (count = 0; node; node = node->next, count++)
	{
		if (node->name)
		{
			if (cmp && (_strspn(node->name, cmp) < (size_t) _strlen(cmp)))
				continue;
			_print(node->name, STDOUT_FILENO), _print("=", STDOUT_FILENO);
			if (node->value)
			{
				_print("'", STDOUT_FILENO), _print(node->value, STDOUT_FILENO);
				_print("'\n", STDOUT_FILENO);
			}
		}
	}

	return (count);
}

/**
 * free_aliaslist - frees memory of alias_d_t list.
 * @head: pto to head ptr to list first elem
 * Return: ptr to new node.
 */
void free_aliaslist(alias_d_t *head)
{
	alias_d_t *next;

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
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head), head = next;
	}
}

/**
 * get_alias_node - gets a node alias_d_t list.
 * @head: pto to head ptr to list first elem
 * @name: name of fnode
 * Return: ptr to node or null
 */
alias_d_t *get_alias_node(alias_d_t *head, char *name)
{
	alias_d_t *node = NULL;

	if (!head)
		return (node);
	/* make sure start of node */
	node = head;
	while (node)
	{
		if (!node->prev)
			break;
		node = node->prev;
	}
	/* iterate foward and free */
	while (node)
	{
		if (_strcmp(name, node->name) == 0)
			return (node);
		node = node->next;
	}

	return (node);
}
