/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_conversions_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:13:06 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 14:43:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	loop_conversions_quotes(t_node *n, t_shell *sh)
{
	size_t	word;
	ssize_t	i;

	word = -1;
	while (n->arg && n->arg[++word] != NULL)
	{
		if (n->arg[word][0] == '~' && (n->arg[word][1] == '/'
			|| n->arg[word][1] == '\0'))
			expansions_tilde(n, sh, word);
		i = -1;
		while (n->arg[word][++i])
		{
			if (n->arg[word][i] == '\\')
				i += remove_backslash(&n->arg[word][i]);
			else if (n->arg[word][i] == '\'')
				i = strip_quotes_single(n->arg[word], i);
			else if (n->arg[word][i] == '\"')
				i = strip_quotes_double(&(n->arg[word]), i, sh);
			else if (n->arg[word][i] == '$')
			{
				printf("\t(%s)\n", (n->arg[word]));
				i = update_arg_dollar(i, &(n->arg[word]), sh) - 1;
			}
		}
	}
}
