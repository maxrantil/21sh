/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 18:11:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node *parse_exec(char **ptr_to_str)
{
	char	*token;
	char	*end_q;
	int		type;
	size_t	argc;
	t_node	*node;

	node = node_create(EXEC, NULL, NULL, NULL);
	node = parse_redirection(node, ptr_to_str);
	argc = 0;
	while (**ptr_to_str && !peek(ptr_to_str, "|&;"))
	{
		type = token_get(ptr_to_str, &token, &end_q);
		if (type == 'a')
			node->arg[argc++] = ft_strsub(token, 0, (size_t)(end_q - token)); //make args a douple pointer instead?
		else if (type == 0)
			break ;
		else
		{
			ft_printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
		node = parse_redirection(node, ptr_to_str);
	}
	if (node)
		node->arg[argc] = NULL;
	return (node);
}