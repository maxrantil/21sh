/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 17:20:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_node_type(char *tok)
{
	while (*tok && !ft_isspace(tok))
	{
		if (ft_isdigit(*tok))
			tok++;
		else
			break ;
	}
	if (*tok == '>' && *(tok + 1) == '>')
		return (4);
	else if (*tok == '>' && *(tok + 1) != '&')
		return (3);
	else if (*tok == '<')
		return (5);
	return (6);
}

static t_node	*make_redir_node(t_node *n, char **ptr_to_line, \
	char *tok, int len)
{
	t_node	*tmp;
	t_node	*hold;
	int		node_type;

	hold = n;
	while (n->left->type != EXEC)
		n = n->left;
	tmp = n->left;
	node_type = get_node_type(tok);
	if (node_type == 4)
		++len;
	tmp = node_create(node_type, tmp, NULL);
	redir_node_add_args(tmp, &ptr_to_line, &tok, len);
	n->left = tmp;
	tmp = NULL;
	n = hold;
	return (n);
}

static void	make_fileagg_node(t_node **n, char **ptr_to_line, char *tok, int fileagg_len)
{
	if ((*n)->type >= REDIROVER && (*n)->type <= FILEAGG)
		*n = make_redir_node(*n, ptr_to_line, tok, fileagg_len);
	else
	{
		*n = node_create(FILEAGG, *n, NULL);
		redir_node_add_args(*n, &ptr_to_line, &tok, fileagg_len);
	}
}

static void	make_fd_node(t_node **n, char **ptr_to_line, char *tok, int fd_len, int type)
{
	if ((*n)->type >= REDIROVER && (*n)->type <= FILEAGG)
	{
		*n = make_redir_node(*n, ptr_to_line, tok, fd_len);
		return ;
	}
	else if (type == '>' || (type == 'a' \
		&& (**ptr_to_line == '>' && *(*ptr_to_line + 1) != '>')))
		*n = node_create(REDIROVER, *n, NULL);
	else if (type == '<' || (type == 'a' && **ptr_to_line == '<'))
		*n = node_create(REDIRIN, *n, NULL);
	else if (type == '#' || (type == 'a' \
		&& (**ptr_to_line == '>' && *(*ptr_to_line + 1) == '>')))
		*n = node_create(REDIRAPP, *n, NULL);
	redir_node_add_args(*n, &ptr_to_line, &tok, fd_len);
}

t_node *parse_redirection(t_node *n, char **ptr_to_line)
{
	char	*tok;
	char	*end_q;
	int		type;
	int		fileagg_len;
	int		fd_len;

	while (n && n->arg && peek(ptr_to_line, "<>&1234567890"))
	{
		type = tok_get(ptr_to_line, &tok, &end_q);
		fileagg_len = check_for_fileagg(tok);
		fd_len = get_fd_before(tok);
		if (n && fileagg_len > 0)
		{
			make_fileagg_node(&n, ptr_to_line, tok, fileagg_len);
			fd_len = 0;
		}
		else if (n && fd_len > 0)
			make_fd_node(&n, ptr_to_line, tok, fd_len, type);
		if (fileagg_len < 0 || fd_len < 0)
			return (error_redir(n, ptr_to_line));
	}
	return (n);
}
