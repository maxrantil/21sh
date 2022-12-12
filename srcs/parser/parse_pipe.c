/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:02:09 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 16:20:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_pipe(t_line *l)
{
	t_node	*n;

	n = parse_exec(l);
	if (n && **l->ptr_to_line && peek(l->ptr_to_line, "|"))
	{
		l->type = tok_get(l->ptr_to_line, &l->tok, &l->end_q);
		if (!peek(l->ptr_to_line, "|&;"))
			n = node_create(PIPE, n, parse_pipe(l));
		else
		{
			ft_putstr_fd("pipie syntax error near unexpected tok `", 2);
			ft_putchar_fd(l->type, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
	}
	return (n);
}
