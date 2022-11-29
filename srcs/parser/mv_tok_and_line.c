/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_tok_and_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:10:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 13:16:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	mv_tok_and_line(char **tok, char ***ptr_to_line, int len)
{
	*tok += len;
	*tok = ft_skip_whitespaces(*tok);
	**ptr_to_line = *tok;
}
