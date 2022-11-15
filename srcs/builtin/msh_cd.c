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
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
}

static void	exec_dash(char **env)
{
	char	cwd[MAX_PATHLEN];
	char	*oldpwd;

	oldpwd = env_getvalue(env, "OLDPWD=");
	if (chdir(oldpwd) != 0)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
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
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	ft_strdel(&home);
}

int	msh_cd(t_node *node, t_msh *msh)
{
	char	cwd[MAX_PATHLEN];

	getcwd(cwd, sizeof(cwd));
	if (ft_arrlen((void **)node->arg) <= 2)
	{
		if (!node->arg[1])
			exec_home(msh->env);
		else if (!ft_strcmp(node->arg[1], "-"))
			exec_dash(msh->env);
		else if (!ft_strcmp(node->arg[1], "~"))
			exec_tilde(node->arg[1]);
		else
		{
			if (chdir(node->arg[1]) != 0)
			{
				print_error(node->arg[1], 5);
				return (1);
			}
		}
		msh->env = pwd_update(msh, cwd);
	}
	else
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	return (1);
}
