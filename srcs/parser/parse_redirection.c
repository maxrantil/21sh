/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/25 20:09:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_fd_before(char *token)
{
	int		ret;

	ret = 0;
	while (*token && !ft_isspace(token))
	{
		if (ft_isdigit(*token) && ++ret)
			token++;
		else
			break ;
	}
	if (*token == '>')
		return (ret + 1);
	else
		return (0);
}

static int	check_for_fileagg(char *token)
{
	int		ret;

	ret = 0;
	while (*token && !ft_isspace(token))
	{
		if (ft_isdigit(*token) && ++ret)
			token++;
		else
			break ;
	}
	if ((*token == '>' && *(token + 1) == '&')
		|| (*token == '&' && *(token + 1) == '>')) // fix here for echo hello 1&>file
		return (ret + 2);
	else
		return (0);
}

static int	get_len_of_next_tok(char *token)
{
	int	ret;

	ret = 0;
	while (*token && !ft_isspace(token))
	{
		if (ft_isascii(*token) && ++ret)
			token++;
		else
			break ;
	}
	return (ret);
}

static t_node	*make_redir_node(t_node *n, char **ptr_to_line, char *token, int len)
{
	t_node	*tmp;
	t_node	*hold;

	hold = n;
	while (n->left->type != EXEC)
		n = n->left;
	tmp = n->left;
	/* if (hold->type == FILEAGG)
	{ */
		tmp = node_create(FILEAGG, tmp, NULL);
		add_to_args(&tmp->arg, ft_strsub(token, 0, len));
		*ptr_to_line += len - 1;
		token += len;
		token = ft_skip_whitespaces(token);
		len = get_len_of_next_tok(token);
		add_to_args(&tmp->arg, ft_strsub(token, 0, len));
		*ptr_to_line += len;
		token += len;
	/* }
	else if (hold->type >= REDIROVER && hold->type <= REDIRIN)
	{
		tmp = node_create(REDIROVER, tmp, NULL);
		add_to_args(&tmp->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		token_get(ptr_to_line, &token, &end_q);
		add_to_args(&tmp->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
	} */
	n->left = tmp;
	tmp = NULL;
	n = hold;
	return (n);
}

t_node *parse_redirection(t_node *n, char **ptr_to_line)
{
	char	*token;
	char	*end_q;
	int		type;
	int		len;
	int		len1;
	static int o;

	while (n && **ptr_to_line && peek(ptr_to_line, "<>&1234567890"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		len = check_for_fileagg(token);
		len1 = get_fd_before(token);
		ft_printf("TOK = %s\n", token);
		/* ft_printf("TYP = %c\n", type); */
		ft_printf("LEN = %d\n", len);
		ft_printf("LEN1 = %d\n", len1);
		ft_printf("p2l = %s\n", *ptr_to_line);
		if (n && len)
		{
			ft_printf("o = %d\n", o++);
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				n = make_redir_node(n, ptr_to_line, token, len);
			else
			{
				n = node_create(FILEAGG, n, NULL);
				add_to_args(&n->arg, ft_strsub(token, 0, len));
				*ptr_to_line += len - 1;
				token += len;
				token = ft_skip_whitespaces(token);
				len = get_len_of_next_tok(token);
				add_to_args(&n->arg, ft_strsub(token, 0, len));
				if (**ptr_to_line)
					*ptr_to_line += len; //maybe -1 here?
				token += len;
			}
			len1 = 0;
		}
		/* else if (token_get(ptr_to_line, &token, &end_q) != 'a' && '&' != *token && !ft_isdigit(*token))
		{
			ft_putstr_fd("redir syntax error near unexpected token `", 2); // make better error handling for `echo hello >`
			ft_putchar_fd(*token, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		} */
		// else if (n && ((type == '>' || type == '#' || type == '<') || (type == 'a' && peek(ptr_to_line, "<>#"))))
		else if (n && len1)
		{
			// token_get(ptr_to_line, &token, &end_q);
			// ft_printf("oDOWN = %d\n", o++);
			/* ft_printf("LOOK = %c\n", (**ptr_to_line + len1 - 1));
			ft_printf("LOOK1 = %c\n", (**ptr_to_line + len1));
			ft_printf("LOOK2 = %c\n", (**ptr_to_line)); */
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				n = make_redir_node(n, ptr_to_line, token, len1);
			else if (type == '>' || (type == 'a' && (**ptr_to_line == '>')))
			{
				ft_printf("HERE????\n");
				n = node_create(REDIROVER, n, NULL);
			}
			else if (type == '<')
				n = node_create(REDIRIN, n, NULL);
			else if (type == '#') // wrong for now >>
				n = node_create(REDIRAPP, n, NULL);
			// add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
			add_to_args(&n->arg, ft_strsub(token, 0, len1));
			*ptr_to_line += len1;
			token += len1;
			token = ft_skip_whitespaces(token);
			len1 = get_len_of_next_tok(token);
			add_to_args(&n->arg, ft_strsub(token, 0, len1));
			*ptr_to_line += len1; //maybe -1 here?
			token += len1;
		}
		len = 0;
		/* len = 0;
		len1 = 0; */
	}
	return (n);
}
