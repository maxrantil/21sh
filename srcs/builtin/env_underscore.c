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

static char	*underscore_change(t_msh *msh)
{
	size_t	last_arg;

	last_arg = ft_arrlen((void **)msh->args) - 1;
	if (!ft_strncmp(msh->args[last_arg], "\0", 1) && last_arg > 0)
		--last_arg;
	return (ft_strjoin("_=", msh->args[last_arg]));
}

char	**env_underscore(t_msh *msh)
{
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "_=", 2))
		{
			ft_strdel(&msh->env[i]);
			msh->env[i] = underscore_change(msh);
		}
		i++;
	}
	return (msh->env);
}
