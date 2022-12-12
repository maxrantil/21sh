/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 13:04:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	setenv_loop(t_shell *sh, char *arg, int flag_temp)
{
	char	*key;
	size_t	i;

	i = 0;
	key = env_key_extract(arg);
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, ft_strlen(key)))
		{
			if (flag_temp)
				vec_push(&sh->v_tmp_env, sh->env[i]);
			sh->env = unsetenv_var(sh->env, key);
			break ;
		}
		i++;
	}
	sh->env = setenv_var(sh->env, key, \
	ft_strchr(arg, '=') + 1);
	ft_strdel(&key);
}
