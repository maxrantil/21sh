/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:02:09 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:34:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_pipe(char **ptr_to_line)
{
	char 	*token;
	char 	*end_q;
	int		type;
	t_node	*n;

	n = parse_exec(ptr_to_line);
	if (peek(ptr_to_line, "|"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		if (!peek(ptr_to_line, "|&;"))
			n = node_create(PIPE, n, parse_pipe(ptr_to_line));
		else
		{
			ft_printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
	}
	return (n);
}
