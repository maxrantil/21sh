/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/02 15:22:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_fd_before(char *tok)
{
	int		ret;

	ret = 0;
	while (*tok && !ft_isspace(tok))
	{
		if (ft_isdigit(*tok) && ++ret)
			tok++;
		else
			break ;
	}
	if (*tok == '>' || *tok == '<')
	{
		if (*tok == '>' && *(tok + 1) == '>')
		{
			if (!ft_isalnum(*(tok + 2)) && !ft_isspace(tok + 2))
				return (-1);
			++ret;
		}
		else if (!ft_isalnum(*(tok + 1)) && !ft_isspace(tok + 1))
			return (-1);
		return (++ret);
	}
	else
		return (0);
}

static int	check_for_fileagg(char *tok)
{
	int		ret;

	ret = 0;
	while (*tok && !ft_isspace(tok))
	{
		if (ft_isdigit(*tok) && ++ret)
			tok++;
		else
			break ;
	}
	if (*tok == '>' && *(tok + 1) == '&')
	{
		if (!ft_isalnum(*(tok + 2)) && !ft_isspace(tok + 2))
				return (-1);
		return (ret + 2);
	}
	else
		return (0);
}

static int	get_len_of_next_tok(char *tok)
{
	int	ret;

	ret = 0;
	while (*tok && !ft_isspace(tok))
	{
		if (ft_isascii(*tok) && ++ret)
			tok++;
		else
			break ;
	}
	return (ret);
}

static void	add_args_to_redir_node(t_node *n, char ***ptr_to_line, char **tok, int len)
{
	add_to_args(&n->arg, ft_strsub(*tok, 0, len));
	mv_tok_and_line(tok, ptr_to_line, len);
	len = get_len_of_next_tok(*tok);
	add_to_args(&n->arg, ft_strsub(*tok, 0, len));
	mv_tok_and_line(tok, ptr_to_line, len);
}

static t_node	*make_redir_node(t_node *n, char **ptr_to_line, \
	char *tok, int len)
{
	t_node	*tmp;
	t_node	*hold;

	hold = n;
	while (n->left->type != EXEC)
		n = n->left;
	tmp = n->left;
	if (hold->type == REDIROVER)
		tmp = node_create(REDIROVER, tmp, NULL);
	else if (hold->type == REDIRAPP && ++len)
		tmp = node_create(REDIRAPP, tmp, NULL);
	else if (hold->type == REDIRIN)
		tmp = node_create(REDIRIN, tmp, NULL);
	else if (hold->type == FILEAGG)
		tmp = node_create(FILEAGG, tmp, NULL);
	add_args_to_redir_node(tmp, &ptr_to_line, &tok, len);
	n->left = tmp;
	tmp = NULL;
	n = hold;
	return (n);
}

t_node *parse_redirection(t_node *n, char **ptr_to_line)
{
	char	*tok;
	char	*end_q;
	int		type;
	int		len;
	int		len1;

	while (n && n->arg && peek(ptr_to_line, "<>&1234567890"))
	{
		type = tok_get(ptr_to_line, &tok, &end_q);
		len = check_for_fileagg(tok);
		len1 = get_fd_before(tok);
		if (n && len > 0)
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				n = make_redir_node(n, ptr_to_line, tok, len);
			else
			{
				n = node_create(FILEAGG, n, NULL);
				add_args_to_redir_node(n, &ptr_to_line, &tok, len);
			}
			len1 = 0;
		}
		else if (n && len1 > 0)
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
			{
				n = make_redir_node(n, ptr_to_line, tok, len1);
				continue ;
			}
			else if (type == '>' || (type == 'a' \
				&& (**ptr_to_line == '>' && (**ptr_to_line + 1) != '>')))
				n = node_create(REDIROVER, n, NULL);
			else if (type == '<' || (type == 'a' && (**ptr_to_line == '<')))
				n = node_create(REDIRIN, n, NULL);
			else if (type == '#' || (type == 'a' \
				&& (**ptr_to_line == '>' && (**ptr_to_line + 1) == '>')))
			{
				n = node_create(REDIRAPP, n, NULL);
				// len1++;
			}
			add_args_to_redir_node(n, &ptr_to_line, &tok, len1);
		}
		if (len < 0 || len1 < 0)
		{
			ft_putstr_fd("21sh: (redir) syntax error near unexpected tok `", 2);
			/* if (*tok && *(tok + 1))
				ft_putchar_fd(*tok, 2); */
			if (**ptr_to_line)
				ft_putchar_fd(**ptr_to_line, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
	}
	return (n);
}
