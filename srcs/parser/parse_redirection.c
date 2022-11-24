/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/24 15:14:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	make_redir_node()

t_node *parse_redirection(t_node *n, char **ptr_to_line)
{
	t_node	*tmp;
	t_node	*hold;
	char	*token;
	char	*end_q;
	int		type;

	while (peek(ptr_to_line, "<>1234567890"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		if (n && ft_isdigit(*token) && *(token + 1) == '>' && *(token + 2) == '&' && (ft_isdigit(*(token + 3)) || *(token + 3) == '-')) // this is a hack
		{
			if (n->type >= REDIROVER && n->type <= REDIRIN)
			{
				hold = n;
				while (n->left->type != EXEC)
					n = n->left;
				tmp = n->left;

				tmp = node_create(FILEAGG, tmp, NULL);
				add_to_args(&tmp->arg, ft_strsub(token, 0, 4)); // 4 here hardcoded
				*ptr_to_line += 4;	// this is a hack 4 is hardcoded

				n->left = tmp;
				tmp = NULL;
				n = hold;
			}
			else
			{
				n = node_create(FILEAGG, n, NULL);
				add_to_args(&n->arg, ft_strsub(token, 0, 4)); // 4 here hardcoded
				*ptr_to_line += 4;	// this is a hack 4 is hardcoded
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
			if (n->type >= REDIROVER && n->type <= FILEAGG)
			{
				hold = n;
				while (n->left->type != EXEC)
					n = n->left;
				tmp = n->left;

				tmp = node_create(REDIROVER, tmp, NULL);
				add_to_args(&tmp->arg, ft_strsub(token, 0, (size_t)(end_q - token)));

				n->left = tmp;
				tmp = NULL;
				n = hold;
			}
			else if (type == '>')
			{
				n = node_create(REDIROVER, n, NULL);
			}
			else if (type == '<')
				n = node_create(REDIRIN, n, NULL);
			else if (type == '#')
				n = node_create(REDIRAPP, n, NULL);
			add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		}
	}
	return (n);
}
