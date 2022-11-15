/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:03:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 14:05:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_line(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	t_node	*node;

	node = parse_pipe(ptr_to_str);
	if (peek(ptr_to_str, "&"))
	{
		token_get(ptr_to_str, &token, &end_q);
		node = node_create(AMP, NULL, node, NULL);
	}
	else if (peek(ptr_to_str, ";"))
	{
		token_get(ptr_to_str, &token, &end_q);
		node = node_create(SEMI, NULL, node, parse_line(ptr_to_str));
	}
	if (peek(ptr_to_str, ""))
	{
		printf("syntax error near unexpected token `newline'\n");
		exit(1);
	}
	return (node);
}
