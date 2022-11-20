/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:16:41 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 17:01:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	exec_tilde(char *arg)
{
	if (chdir(arg) != 0)
		ft_putstr_fd("21sh: cd: HOME not set\n", STDERR_FILENO);
}

static void	exec_dash(char **env)
{
	char	cwd[MAX_PATHLEN];
	char	*oldpwd;

	oldpwd = env_getvalue(env, "OLDPWD=");
	if (chdir(oldpwd) != 0)
		ft_putstr_fd("21sh: cd: OLDPWD not set\n", STDERR_FILENO);
	else
	{
		getcwd(cwd, sizeof(cwd));
		ft_printf("%s\n", cwd);
	}
	ft_strdel(&oldpwd);
}

static void	exec_home(char **env)
{
	char	*home;

	home = env_getvalue(env, "HOME=");
	if (chdir(home) != 0)
		ft_putstr_fd("21sh: cd: HOME not set\n", STDERR_FILENO);
	ft_strdel(&home);
}

int	msh_cd(t_node *n, t_shell *sh)
{
	char	cwd[MAX_PATHLEN];

	getcwd(cwd, sizeof(cwd));
	if (ft_arrlen((void **)n->arg) <= 2)
	{
		if (!n->arg[1])
			exec_home(sh->env);
		else if (!ft_strcmp(n->arg[1], "-"))
			exec_dash(sh->env);
		else if (!ft_strcmp(n->arg[1], "~"))
			exec_tilde(n->arg[1]);
		else
		{
			if (chdir(n->arg[1]) != 0)
			{
				error_print(n->arg[1], 5);
				return (1);
			}
		}
		sh->env = pwd_update(sh, cwd);
	}
	else
		ft_putstr_fd("21sh: cd: too many arguments\n", STDERR_FILENO);
	return (1);
}
