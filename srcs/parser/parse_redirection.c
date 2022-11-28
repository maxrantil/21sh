/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/28 16:12:07 by mrantil          ###   ########.fr       */
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
	if ((*token == '>' && *(token + 1) == '&'))
		/* || (*token == '&' && *(token + 1) == '>')) */ // fix here for echo hello 1&>file
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

static void	add_args_to_redir_node(t_node *n, char ***ptr_to_line, char **token, int len)
{
	add_to_args(&n->arg, ft_strsub(*token, 0, len));
	**ptr_to_line += 1;
	*token += len;
	*token = ft_skip_whitespaces(*token);
	len = get_len_of_next_tok(*token);
	add_to_args(&n->arg, ft_strsub(*token, 0, len));
	**ptr_to_line += 1;
	*token += len;
}

static t_node	*make_redir_node(t_node *n, char **ptr_to_line, \
	char *token, int len)
{
	t_node	*tmp;
	t_node	*hold;

	hold = n;
	while (n->left->type != EXEC)
		n = n->left;
	tmp = n->left;
	tmp = node_create(n->type, tmp, NULL);
	/* add_to_args(&tmp->arg, ft_strsub(token, 0, len));
	*ptr_to_line += 1;
	token += len;
	token = ft_skip_whitespaces(token);
	len = get_len_of_next_tok(token);
	add_to_args(&tmp->arg, ft_strsub(token, 0, len));
	*ptr_to_line += 1;
	token += len; */
	add_args_to_redir_node(tmp, &ptr_to_line, &token, len);
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

	while (n && peek(ptr_to_line, "<>&1234567890"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		len = check_for_fileagg(token);
		len1 = get_fd_before(token);
		if (n && len)
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				n = make_redir_node(n, ptr_to_line, token, len);
			else
			{
				n = node_create(FILEAGG, n, NULL);
				add_args_to_redir_node(n, &ptr_to_line, &token, len);
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
		else if (n && len1)
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
			{
				n = make_redir_node(n, ptr_to_line, token, len1);
				continue ;
			}
			else if (type == '>' || (type == 'a' \
				&& (**ptr_to_line == '>' && (**ptr_to_line + 1) != '>')))
				n = node_create(REDIROVER, n, NULL);
			else if (type == '<' || (type == 'a' && (**ptr_to_line == '<')))
				n = node_create(REDIRIN, n, NULL);
			else if (type == '#' || (type == 'a' \
				&& (**ptr_to_line == '>' && (**ptr_to_line + 1) == '>')))
				n = node_create(REDIRAPP, n, NULL);
			add_args_to_redir_node(n, &ptr_to_line, &token, len1);
		}
	}
	return (n);
}
