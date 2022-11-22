/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:00:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:35:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*parse_redirection(t_node *n, char **str)
{
	char	*token;
	char	*end_q;
	int		type;

	while (peek(str, "<>"))
	{
		type = token_get(str, &token, 0);
				ft_printf("token: %s\n", token);
		if (token_get(str, &token, &end_q) != 'a')
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);	//make better error handling for `echo hello >`
			ft_putchar_fd(*token, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
		//if here: token == file name
		if (type == '>' || type == '<')
		{
			if (peek(str, "&"))
			{
				// token_get(str, &token, &end_q);
				ft_printf("token: %s\n", token);
				n = node_create(FILEAGG, n, NULL);
			}
			else if (type == '>')
				n = node_create(REDIROVER, n, NULL);
			else
				n = node_create(REDIRIN, n, NULL);
			add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		}
	}
	return (n);
}
