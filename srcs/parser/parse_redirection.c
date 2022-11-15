/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 18:19:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_redirection(t_node *node, char **str)
{
	char	*token;
	char	*end_q;
	int		type;

	while (peek(str, "<>"))
	{
		type = token_get(str, &token, 0);
		if (token_get(str, &token, &end_q) != 'a')
		{
			ft_printf("\nsyntax error near unexpected token `%c'\n", *token);//make better error handling for `echo hello >`
			return (NULL);
		}
		//if here: token == file name
		if (type == '>' || type == '<')
		{
			if (type == '>')
				node = node_create(REDIROVER, NULL, node, NULL);
			else
				node = node_create(REDIRIN, NULL, node, NULL);
			node->arg[0] = ft_strsub(token, 0, (size_t)(end_q - token));
		}
	}
	return (node);
}
