/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/28 16:59:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node *parse_exec(char **ptr_to_line)
{
	t_node	*n;
	char	*token;
	char	*end_q;
	int		type;

	n = node_create(EXEC, NULL, NULL);
	n = parse_redirection(n, ptr_to_line);
	while (n && !peek(ptr_to_line, "|&;")) // '&' here? //maybe need to go if fd is not specified for redir
	{
		type = token_get(ptr_to_line, &token, &end_q);
		if (type == 'a')
		{
			if (n->type >= REDIROVER && n->type <= FILEAGG)
			{
				t_node	*tmp;
				t_node	*hold;

				hold = n;
				while (n && n->type != EXEC)
					n = n->left;
				tmp = n;
				add_to_args(&tmp->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
				/* n->left = tmp; */
				tmp = NULL;
				n = hold;
			}
			else
				add_to_args(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		}
		else if (type == 0)
			break ;
		else
		{
			ft_putstr_fd("exec syntax error near unexpected token `", 2);
			ft_putchar_fd(type, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
		n = parse_redirection(n, ptr_to_line);
	}
	return (n);
}

