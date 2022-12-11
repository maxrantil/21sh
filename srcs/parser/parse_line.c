/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:03:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 11:59:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_line(char **ptr_to_line)
{
	char 	*tok;
	char 	*end_q;
	t_node	*n;

	n = parse_pipe(ptr_to_line);
	if (n && peek(ptr_to_line, "&"))
	{
		tok_get(ptr_to_line, &tok, &end_q);
		n = node_create(AMP, n, NULL);
	}
	else if (n && peek(ptr_to_line, ";"))
	{
		tok_get(ptr_to_line, &tok, &end_q);
		n = node_create(SEMI, n, parse_line(ptr_to_line));
	}
	if (peek(ptr_to_line, ""))
	{
		ft_putendl_fd("syntax error near unexpected tok `newline'", 2);
		tree_free(n);
		return (NULL);
	}
	return (n);
}
