/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/25 16:34:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

static t_node	*make_redir_node(t_node *n, char **ptr_to_line, char *token, char *end_q, int len)
{
	t_node	*tmp;
	t_node	*hold;

	hold = n;
	while (n->left->type != EXEC)
		n = n->left;
	tmp = n->left;
	if (hold->type == FILEAGG)
	{
		tmp = node_create(FILEAGG, tmp, NULL);
		add_to_args(&tmp->arg, ft_strsub(token, 0, len));
		*ptr_to_line += len - 1;
		token += len;
		token = ft_skip_whitespaces(token);
		len = get_len_of_next_tok(token);
		add_to_args(&tmp->arg, ft_strsub(token, 0, len));
		*ptr_to_line += len;
		token += len;
	}
	else if (hold->type >= REDIROVER && hold->type <= REDIRIN)
	{
		tmp = node_create(REDIROVER, tmp, NULL);
		add_to_args(&tmp->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		token_get(ptr_to_line, &token, &end_q);
		add_to_args(&tmp->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
	}
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
	static int o;

	while (n && peek(ptr_to_line, "<>&1234567890"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		len = check_for_fileagg(token);
		ft_printf("TOK = %s\n", token);
		if (n && len)
		{
			ft_printf("o = %d\n", o++);
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				n = make_redir_node(n, ptr_to_line, token, end_q, len);
			else
			{
				n = node_create(FILEAGG, n, NULL);
				add_to_args(&n->arg, ft_strsub(token, 0, len));
				*ptr_to_line += len - 1;
				token += len;
				token = ft_skip_whitespaces(token);
				len = get_len_of_next_tok(token);
				add_to_args(&n->arg, ft_strsub(token, 0, len));
				*ptr_to_line += len; //maybe -1 here?
				token += len;
			}
		}
		else if (token_get(ptr_to_line, &token, &end_q) != 'a' && '&' != *token && !ft_isdigit(*token))
		{
			ft_putstr_fd("redir syntax error near unexpected token `", 2); // make better error handling for `echo hello >`
			ft_putchar_fd(*token, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
		else if (n && (type == '>' || type == '#' || type == '<'))
		{
			ft_printf("oDOWN = %d\n", o++);
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				n = make_redir_node(n, ptr_to_line, token, end_q, 0);
			else if (type == '>')
				n = node_create(REDIROVER, n, NULL);
			else if (type == '<')
				n = node_create(REDIRIN, n, NULL);
			else if (type == '#')
				n = node_create(REDIRAPP, n, NULL);
			add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		}
	}
	return (n);
}
