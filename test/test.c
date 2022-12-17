#include "../token.h"

int main(void)
{
	cmd_prop_t *head = NULL, *tmp = NULL;
	char *cmd = NULL, **arg_list = NULL;
	int list_s = 0, i = 0;

	cmd = strdup("ls ff gg bbres  ; ls 000-la ; ls ./curr || ls -la dd");

	printf("Resul: %d \n", inp_tok(cmd, &head));
	print_cmdlist(head);

	tmp = head;
	while (tmp)
	{
		arg_list = arg_tok(tmp->cmd, " ", &list_s);
		if (arg_list)
		{
			for (i = 0; arg_list[i]; i++)
			{
				printf("Token:%s ", arg_list[i]);
			}
			printf("list size: %d \n", list_s);
			free(arg_list);
		}
		tmp = tmp->next;
	}

	free_cmdlist(head);
	free(cmd);
	return (0);
}
