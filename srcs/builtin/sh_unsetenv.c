/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/06 14:46:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	loop_for_unsetenv(t_shell *sh, char *arg)
{
	char	*key;
	size_t	i;
	size_t	len;

	i = 0;
	key = env_key_extract(arg);
	len = ft_strlen(key);
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, len))
		{
			sh->env = unsetenv_var(sh->env, key);
			break ;
		}
		i++;
	}
	ft_strdel(&key);
	return (1);
}

int	sh_unsetenv(t_node *n, t_shell *sh)
{
	size_t	i;

	i = 1;
	while (n->arg[i])
		loop_for_unsetenv(sh, n->arg[i++]);
	i = 0;
	if (sh->temp_env)
		while (sh->temp_env[i])
			loop_for_unsetenv(sh, sh->temp_env[i++]);
	return (1);
}
