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
	t_node	*n;

	n = parse_pipe(ptr_to_line);
	if (peek(ptr_to_line, "&"))
	{
		token_get(ptr_to_line, &token, &end_q);
		n = node_create(AMP, n, NULL);
	}
	else if (peek(ptr_to_line, ";"))
	{
		token_get(ptr_to_line, &token, &end_q);
		n = node_create(SEMI, n, parse_line(ptr_to_line));
	}
	if (peek(ptr_to_line, ""))
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		exit(1);
	}
	return (n);
}
