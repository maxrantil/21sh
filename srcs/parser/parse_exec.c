/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/07 15:20:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	add_quote_tok(char *tok, int quote)
{
	int len;

	len = 1;
	tok++;
	while (*tok && *tok != quote && ++len)
		tok++;
	return (++len);
}

t_node *parse_exec(char **ptr_to_line)
{
	t_node	*n;
	char	*tok;
	char	*end_q;
	int		type;

	n = node_create(EXEC, NULL, NULL);
	n = parse_redirection(n, ptr_to_line);
	while (n && !peek(ptr_to_line, "|&;")) // '&' here? //maybe need to go if fd is not specified for redir
	{
		type = tok_get(ptr_to_line, &tok, &end_q);
		if (type == 'a')
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
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
			else
			{
				int len = add_quote_tok(tok, *tok);
				if (*tok == '"' || *tok == '\'')
				{
					add_to_args(&n->arg, ft_strsub(tok, 0, len));
					mv_tok_and_line(&tok, &ptr_to_line, len);
				}
				else
					add_to_args(&n->arg, ft_strsub(tok, 0, (size_t)(end_q - tok)));
			}
		}
		else if (type == 0)
			break ;
		else
		{
			ft_putstr_fd("exec syntax error near unexpected tok `", 2);
			ft_putchar_fd(type, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
		if (ft_strcspn(tok, "<>"))
			n = parse_redirection(n, ptr_to_line);
	}
	return (n);
}

