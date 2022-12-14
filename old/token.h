#ifndef TOKEN_H
#define TOKEN_H /* TOKEN_H */

/* start */
#include "utils.h"

/* typedef for token list flag enum */
/**
 * enum token_flag - flag types
 * @CMD_TOK: token is a command
 * @OPR_TOK: token is an operator
 * @PRM_TOK: tok..
 */
typedef enum token_flag
{ CMD_TOK = 0, OPR_TOK = 2, PRM_TOK = 4 } token_flag_t;

/**
 * struct token_list - list of tokens and their types
 * @token: the token, null terminated string
 * @flag: the flag/type of the token
 * @next: pointer to next token
 * @prev: pointer to prev token
 */
typedef struct token_list
{
	char *token;
	token_flag_t flag;
	struct token_list *next;
	struct token_list *prev;
} token_list_t;

/* functions */
token_list_t *add_node(token_list_t **head, char *str, token_flag_t flag);
token_list_t *add_node_end(token_list_t **head, char *str, token_flag_t flag);
char **tokenize_tl(char *input_b, char *delim,
	token_list_t **token_list, int *l_size);
void free_list(token_list_t **head);
char **tokenize_args(char *input_b, char *delim, int argc);

/* new */

/* cmd_list functions */
cmd_prop_t *add_node_cmd_end(cmd_prop_t **head, char *buf, int n);
size_t cmdlist_len(const cmd_prop_t *head);
size_t print_cmdlist(const cmd_prop_t *head);
int inp_tok(char *buffer, cmd_prop_t **head);
void free_cmdlist(cmd_prop_t *head);

/* arg_list functions */
char **arg_tok(char *input_b, char *delim, int *l_size);
arg_list_t *add_node_argl_end(arg_list_t **head, char *str);
void free_arg_list(arg_list_t *head);
int cmd_to_args(cmd_prop_t *cmd_list);
int print_args_cmdlist(cmd_prop_t *cmd_list);

#endif /* TOKEN_H */
