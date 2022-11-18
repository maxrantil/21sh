/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:03:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:34:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_line(char **ptr_to_line)
{
	char 	*token;
	char 	*end_q;
	t_node	*node;

	node = parse_pipe(ptr_to_line);
	if (peek(ptr_to_line, "&"))
	{
		token_get(ptr_to_line, &token, &end_q);
		node = node_create(AMP, node, NULL);
	}
	else if (peek(ptr_to_line, ";"))
	{
		token_get(ptr_to_line, &token, &end_q);
		node = node_create(SEMI, node, parse_line(ptr_to_line));
	}
	if (peek(ptr_to_line, ""))
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		exit(1);
	}
	return (node);
}
