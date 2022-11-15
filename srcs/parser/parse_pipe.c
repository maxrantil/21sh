/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:02:09 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 18:11:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_pipe(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	int		type;
	t_node	*node;

	node = parse_exec(ptr_to_str);
	if (peek(ptr_to_str, "|"))
	{
		type = token_get(ptr_to_str, &token, &end_q);
		if (!peek(ptr_to_str, "|&;"))
			node = node_create(PIPE, NULL, node, parse_pipe(ptr_to_str));
		else
		{
			ft_printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
	}
	return (node);
}
