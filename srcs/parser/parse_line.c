/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:03:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 16:20:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_line(t_line *l)
{
	t_node	*n;

	n = parse_pipe(l);
	if (n && peek(l->ptr_to_line, ";"))
	{
		tok_get(l->ptr_to_line, &l->tok, &l->end_q);
		n = node_create(SEMI, n, parse_line(l));
	}
	if (peek(l->ptr_to_line, ""))
	{
		ft_putendl_fd("syntax error near unexpected tok `newline'", 2);
		tree_free(n);
		return (NULL);
	}
	return (n);
}
