/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 18:22:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static size_t	find_variables(t_node *n, t_shell *sh, size_t i, size_t j)
{
	if (n->arg[i][j] == '~' && j == 0)
	{
		expansions_tilde(n, sh, i);
	}
	if (n->arg[i][j] == '$' \
		&& (n->arg[i][j + 1] == '_' \
		|| ft_isalnum(n->arg[i][j + 1])))
	{
		expansions_dollar(n, sh, ft_strchr(n->arg[i], '$'), i);
		return (1);
	}
	else if (n->arg[i][j] == '$' \
		&& n->arg[i][j + 1] == '$')
	{
		ft_strdel(&n->arg[i]);
		n->arg[i] = ft_itoa(getpid());
	}
	return (0);
}

void	expansions(t_node *n, t_shell *sh)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (n->arg && n->arg[i])
	{
		j = 0;
		while (n->arg[i][j])
		{
			if (find_variables(n, sh, i, j))
				break ;
			j++;
		}
		i++;
	}
}
