/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_conversions_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:13:06 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 14:13:57 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	loop_conversions_quotes(t_node *n, t_shell *sh)
{
	size_t	word;
	size_t	i;

	word = -1;
	while (n->arg[++word] != NULL)
	{
		if (n->arg[word][0] == '~' && (n->arg[word][1] == '/'
			|| n->arg[word][1] == '\0'))
			expansions_tilde(n, sh, word);
		i = -1;
		while (n->arg[word][++i])
		{
			if (n->arg[word][i] == '\\')
				remove_backslash(&n->arg[word][i]);
			else if (n->arg[word][i] == '\'')
				i = strip_quotes_single(n->arg[word], i);
			else if (n->arg[word][i] == '\"')
				i = strip_quotes_double(&(n->arg[word]), i);
			else if (n->arg[word][i] == '$')
				i = update_arg_dollar(i, &(n->arg[word]), 0, 0) - 1;
		}
	}
}
