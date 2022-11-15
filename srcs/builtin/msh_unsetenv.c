/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 16:58:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	loop_for_unsetenv(t_msh *msh, char *arg)
{
	char	*key;
	size_t	i;
	size_t	len;

	i = 0;
	key = env_key_extract(arg);
	len = ft_strlen(key);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], key, len))
		{
			msh->env = unsetenv_var(msh->env, key);
			break ;
		}
		i++;
	}
	ft_strdel(&key);
	return (1);
}

int	msh_unsetenv(t_node *node, t_msh *msh)
{
	size_t	i;

	i = 1;
	while (node->arg[i])
		loop_for_unsetenv(msh, node->arg[i++]);
	i = 0;
	if (msh->temp_env)
		while (msh->temp_env[i])
			loop_for_unsetenv(msh, msh->temp_env[i++]);
	return (1);
}
