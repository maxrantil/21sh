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

static size_t	find_variables(t_node *node, t_msh *msh, size_t i, size_t j)
{
	if (node->arg[i][j] == '~' && j == 0)
	{
		expansions_tilde(node, msh, i);
	}
	if (node->arg[i][j] == '$' \
		&& (node->arg[i][j + 1] == '_' \
		|| ft_isalnum(node->arg[i][j + 1])))
	{
		expansions_dollar(node, msh, ft_strchr(node->arg[i], '$'), i);
		return (1);
	}
	else if (node->arg[i][j] == '$' \
		&& node->arg[i][j + 1] == '$')
	{
		ft_strdel(&node->arg[i]);
		node->arg[i] = ft_itoa(getpid());
	}
	return (0);
}

void	expansions(t_node *node, t_msh *msh)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (node->arg[i])
	{
		j = 0;
		while (node->arg[i][j])
		{
			if (find_variables(node, msh, i, j))
				break ;
			j++;
		}
		i++;
	}
}
