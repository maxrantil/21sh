/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 16:05:21 by mrantil          ###   ########.fr       */
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
	int len;

	len = 1;
	tok++;
	while (*tok && *tok != quote && ++len)
		tok++;
	while (*tok && !ft_isspace((const char *)tok) && ++len)
		tok++;
	return (len);
}

static int	is_quote_somewhere(char *tok)
{
	int	quote;
	int	len;

	len = 0;
	while (*tok && !ft_isspace((const char *)tok) && ++len)
	{
		if (*tok == '\'' || *tok == '"') // && *tok - 1 != '\'
		{
			quote = *tok;
			++tok;
			while (*tok != quote && ++len)
				tok++;
			while (*tok && !ft_isspace((const char *)tok) && ++len)
				tok++;
			if (*tok == '\'' || *tok == '"') // && *tok - 1 != '\'
				continue ;
			return (len);

		}
		tok++;
	}
	return (0);
}

static	void exec_create(t_node *n, char **ptr_to_line, char *tok, char *end_q)
{
	int len;
	int	has_quote;

	has_quote = is_quote_somewhere(tok);
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

// static int	check_tok_for_redir(char *tok, char *end_q)
// {
// 	char	*check;
// 	int		ret;

// 	check = ft_strsub(tok, 0, end_q - tok);
// 	if (ft_strcspn(check, "<>"))
// 		ret = 1;
// 	else
// 		ret = 0;
// 	ft_strdel(&check);
// 	return (ret);
// }

t_node	*parse_exec(t_line *l)
{
	t_node	*n;

	n = node_create(EXEC, NULL, NULL);
	n = parse_redirection(n, l);
	while (n && !peek(l->ptr_to_line, "|&;"))
	{
		l->type = tok_get(l->ptr_to_line, &l->tok, &l->end_q);
		if (l->type == 'a')
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
				exec_create_redir(n, l->tok, l->end_q);
			else
				exec_create(n, l->ptr_to_line, l->tok, l->end_q);
		}
		else if (l->type == 0)
			break ;
		else /* if (type != '#' || type != '<' || type != '>') */
			return (exec_error(n, l->type));
		// if (check_tok_for_redir(tok, end_q)) //this needs to fixed so it just check one work and not
		n = parse_redirection(n, l);
	}
	return (n);
}
