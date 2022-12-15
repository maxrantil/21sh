/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 12:02:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	exec_create_redir(t_node *n, char *tok, char *end_q)
{
	t_node	*tmp;
	t_node	*hold;

	hold = n;
	while (n && n->type != EXEC)
		n = n->left;
	tmp = n;
	add_to_args(&tmp->arg, ft_strsub(tok, 0, (size_t)(end_q - tok)));
	tmp = NULL;
	n = hold;
}

static int	add_quote_tok(char *tok, int quote)
{
	int	len;

	len = 1;
	tok++;
	while (*tok && *tok != quote && ++len)
		tok++;
	while (*tok && !ft_isspace((const char *)tok) && ++len)
		tok++;
	return (len);
}

static void	exec_create(t_node *n, char **ptr_to_line, char *tok, char *end_q)
{
	int	len;
	int	has_quote;

	has_quote = exec_is_quote_somewhere(tok);
	if ((*tok == '"' || *tok == '\'') && !has_quote)
	{
		len = add_quote_tok(tok, *tok);
		add_to_args(&n->arg, ft_strsub(tok, 0, len));
		mv_tok_and_line(&tok, &ptr_to_line, len);
	}
	else if (has_quote)
	{
		add_to_args(&n->arg, ft_strsub(tok, 0, has_quote));
		mv_tok_and_line(&tok, &ptr_to_line, has_quote);
	}
	else
		add_to_args(&n->arg, ft_strsub(tok, 0, (size_t)(end_q - tok)));
}

t_node	*parse_exec(t_line *l, char **ptr_to_line)
{
	t_node	*n;

	n = node_create(EXEC, NULL, NULL);
	n = parse_redirection(n, l, ptr_to_line);
	while (n && !peek(ptr_to_line, "|&;"))
	{
		l->type = tok_get(ptr_to_line, &l->tok, &l->end_q);
		if (l->type == 'a')
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				exec_create_redir(n, l->tok, l->end_q);
			else
				exec_create(n, ptr_to_line, l->tok, l->end_q);
		}
		else if (l->type == 0)
			break ;
		else
			return (exec_error(n, l->type));
		n = parse_redirection(n, l, ptr_to_line);
	}
	return (n);
}
