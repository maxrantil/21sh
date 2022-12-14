/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:28:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 12:59:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	**change_pwd(char **env, char *cwd, char *key)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			ft_strdel(&env[i]);
			env[i] = ft_strjoin(key, cwd);
			return (env);
		}
		i++;
	}
	return (setenv_var(env, key, cwd));
}

char	**pwd_update(t_shell *sh, char *oldcwd)
{
	char	cwd[MAX_PATHLEN];

	sh->env = change_pwd(sh->env, oldcwd, "OLDPWD=");
	getcwd(cwd, sizeof(cwd));
	sh->env = change_pwd(sh->env, cwd, "PWD=");
	return (sh->env);
}
