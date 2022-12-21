/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node_add_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:31:32 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/21 17:25:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_len_of_next_tok(char *tok)
{
	int	ret;

	ret = 0;
	while (*tok && !ft_isspace(tok) && *tok != '&' && *tok != '|' \
		&& *tok != '<' && *tok != '>' && *tok != ';')
	{
		if (ft_isascii(*tok) && ++ret)
			tok++;
		else
			break ;
	}
	return (ret);
}

void	redir_node_add_args(t_node *n, char ***ptr_to_line, char **tok, int len)
{
	add_to_args(&n->arg, ft_strsub(*tok, 0, len));
	mv_tok_and_line(tok, ptr_to_line, len);
	len = get_len_of_next_tok(*tok);
	add_to_args(&n->arg, ft_strsub(*tok, 0, len));
	mv_tok_and_line(tok, ptr_to_line, len);
}
