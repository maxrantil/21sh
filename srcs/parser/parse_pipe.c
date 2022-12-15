/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:02:09 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 10:20:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_pipe(t_line *l, char **ptr_to_line)
{
	t_node	*n;

	n = parse_exec(l, ptr_to_line);
	if (n && **ptr_to_line && peek(ptr_to_line, "|"))
	{
		l->type = tok_get(ptr_to_line, &l->tok, &l->end_q);
		if (!peek(ptr_to_line, "|&;"))
			n = node_create(PIPE, n, parse_pipe(l, ptr_to_line));
		else
		{
			ft_putstr_fd("(pipe) syntax error near unexpected tok `", 2);
			ft_putchar_fd(l->type, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
	}
	return (n);
}
