/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_tok_and_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:10:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 13:28:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	mv_tok_and_line(char **tok, char ***ptr_to_line, int len)
{
	*tok += len;
	if (*tok)
		**ptr_to_line = *tok;
	*tok = ft_skip_whitespaces(*tok);
	if (*tok)
		**ptr_to_line = *tok;
}
