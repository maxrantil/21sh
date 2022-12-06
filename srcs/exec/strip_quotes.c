/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:18:22 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/02 18:59:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void	strip_quotes(t_node *n, t_shell *sh)
{
	ssize_t	i;
	ssize_t	j;
	size_t	len;
	ssize_t	quote1;
	ssize_t	quote2;

	len = 0;
	j = 0;
	ft_printf("STRIP_QUOTES: %s\n", n->arg[0]);
	while (n->arg[j])
	{
		i = 0;
		if (n->arg[j][i] == '\"')
			expansions(n, sh);
		len = ft_strlen(n->arg[j]);
		while (n->arg[j][i])
		{
			if (n->arg[j][i] == '\'' || n->arg[j][i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&n->arg[j][i], n->arg[j][i]);
				quote2 += quote1;
				ft_memmove((void *)&n->arg[j][i], \
				(void *)&n->arg[j][i + 1], len - (size_t)quote1);
				ft_memmove((void *)&n->arg[j][quote2 - 1], \
				(void *)&n->arg[j][quote2], len - (size_t)quote2);
				i = quote2 - 2;
			}
			i++;
		}
		if (n->arg[j])
			n->arg[j++];
	}
}
