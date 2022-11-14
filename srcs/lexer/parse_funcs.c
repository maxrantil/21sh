#include "parser.h"

t_node	*create_node(int type, t_node *sub_cmd, t_node *left, t_node *right)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = type;
	node->command = sub_cmd;
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*parse_redirection(t_node *node, char **str)
{
	char	*token;
	char	*end_q;
	int		type;

	while (peek(str, "<>"))
	{
		type = get_token(str, &token, 0);
		if (get_token(str, &token, &end_q) != 'a')
		{
			printf("syntax error near unexpected token `redirect'\n");
			exit(1);
		}
		//if here: token == file name
		if (type == '>' || type == '<')
		{
			if (type == '>')
				node = create_node(REDIROVER, NULL, node, NULL);
			else
				node = create_node(REDIRIN, NULL, node, NULL);
			node->arg[0] = ft_strsub(token, 0, (size_t)(end_q - token));
		}
	}
	return (node);
}

t_node *parse_exec(char **ptr_to_str)
{
	char	*token;
	char	*end_q;
	int		type;
	size_t	argc;
	t_node	*node;

	node = create_node(EXEC, NULL, NULL, NULL);
	node = parse_redirection(node, ptr_to_str);
	argc = 0;
	while (**ptr_to_str && !peek(ptr_to_str, "|&;"))
	{
		type = get_token(ptr_to_str, &token, &end_q);
		if (type == 'a')
			node->arg[argc++] = ft_strsub(token, 0, (size_t)(end_q - token));
		else if (type == 0)
			break ;
		else
		{
			printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
		node = parse_redirection(node, ptr_to_str);
	}
	node->arg[argc] = NULL;
	return (node);
}

t_node	*parse_pipe(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	int		type;
	t_node	*node;

	node = parse_exec(ptr_to_str);
	if (peek(ptr_to_str, "|"))
	{
		type = get_token(ptr_to_str, &token, &end_q);
		if (!peek(ptr_to_str, "|&;"))
			node = create_node(PIPE, NULL, node, parse_pipe(ptr_to_str));
		else
		{
			printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
	}
	return (node);
}

t_node	*parse_line(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	t_node	*node;

	node = parse_pipe(ptr_to_str);
	if (peek(ptr_to_str, "&"))
	{
		get_token(ptr_to_str, &token, &end_q);
		node = create_node(AMP, NULL, node, NULL);
	}
	else if (peek(ptr_to_str, ";"))
	{
		get_token(ptr_to_str, &token, &end_q);
		node = create_node(SEMI, NULL, node, parse_line(ptr_to_str));
	}
	if (peek(ptr_to_str, ""))
	{
		printf("syntax error near unexpected token `newline'\n");
		exit(1);
	}
	return (node);
}
