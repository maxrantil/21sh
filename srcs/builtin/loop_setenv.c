/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 15:52:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	loop_setenv(t_msh *msh, char *arg)
{
	char	*key;
	size_t	i;

	i = 0;
	key = extract_key(arg);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
		{
			msh->env = unset_env_var(msh->env, key);
			break ;
		}
		i++;
	}
	msh->env = set_env_var(msh->env, key, \
	ft_strchr(arg, '=') + 1);
	ft_strdel(&key);
}
