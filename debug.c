#include "shell.h"

/**
 * print_cmdlist - prints all the elements of a cmd_prop_t list..
 * @head: head ptr to list first elem
 * Return: list size .
 * Description: debug only function
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
 * print_args_cmdlist - debug, print args
 * @cmd_list: head
 * Return: 0 on success
 * Description: debug only function
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

/**
 * print_aliaslist - prints all the elements of a alias_d_t list..
 * @head: head ptr to list first elem
 * @cmp: str to cmp to, if NULl cmp wont be done
 * Return: list size .
 * Description: not debug only, can be used
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
