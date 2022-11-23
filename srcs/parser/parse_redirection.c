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

t_node *parse_redirection(t_node *n, char **ptr_to_line)
{
	char *token;
	char *end_q;
	int type;

	while (peek(ptr_to_line, "<>1234567890"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		ft_printf("type: %d\n", type);
		ft_printf("token: %s\n", token);
		if (ft_strcspn("<>", token) && ft_strchr(token, '&'))
		{
			n = node_create(FILEAGG, n, NULL);
			add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
			token_get(ptr_to_line, &token, &end_q);
			// token_get(ptr_to_line, &token, &end_q);
			// token_get(ptr_to_line, &token, &end_q);
			// parse_redirection(n, ptr_to_line);
		}
		// if (peek(ptr_to_line, "1234567890")) //may need '&' here too
			// n = parse_fileagg(n, ptr_to_line); //else if after?
		if (token_get(ptr_to_line, &token, &end_q) != 'a' && '&' != *token && !ft_isdigit(*token))
		{
			ft_putstr_fd("redir syntax error near unexpected token `", 2); // make better error handling for `echo hello >`
			ft_putchar_fd(*token, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
		if (n && (type == '>' || type == '#' || type == '<'))
		{
			if (type == '>')
				n = node_create(REDIROVER, n, NULL);
			else if (type == '<')
				n = node_create(REDIRIN, n, NULL);
			else if (type == '#')
				n = node_create(REDIRAPP, n, NULL);
			add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		}
	}
	return (n);
}
