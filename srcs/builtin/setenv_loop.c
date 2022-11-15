/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 13:00:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	setenv_loop(t_msh *msh, char *arg, int flag_temp)
{
	char	*key;
	size_t	i;

	i = 0;
	key = env_key_extract(arg);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
		{
			if (flag_temp)
				vec_push(&msh->v_temp, msh->env[i]); //some read memory error, valgrind it later
			msh->env = unsetenv_var(msh->env, key);
			break ;
		}
		i++;
	}
	msh->env = setenv_var(msh->env, key, \
	ft_strchr(arg, '=') + 1);
	ft_strdel(&key);
}
