/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_underscore.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:28:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:47:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*underscore_change(t_node *n)
{
	size_t	last_arg;

	last_arg = ft_arrlen((void **)n->arg) - 1;
	if (!ft_strncmp(n->arg[last_arg], "\0", 1) && last_arg > 0)
		--last_arg;
	return (ft_strjoin("_=", n->arg[last_arg]));
}

char	**env_underscore(t_node *n, t_shell *sh)
{
	size_t	i;

	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], "_=", 2))
		{
			ft_strdel(&sh->env[i]);
			sh->env[i] = underscore_change(n);
		}
		i++;
	}
	return (sh->env);
}
