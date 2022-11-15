/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 12:55:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_user(t_msh *msh, char **tilde, size_t i)
{
	struct dirent	*dirp;
	DIR				*dp;
	size_t			len;

	dp = opendir("/Users");
	if (!dp)
		return (0);
	while (1)
	{
		dirp = readdir(dp);
		if (!dirp)
			break ;
		len = ft_strlen(dirp->d_name);
		if (!ft_strncmp(dirp->d_name, (const char *)&msh->args[i][1], len))
		{
			*tilde = ft_strdup("/Users/");
			*tilde = ft_strupdate(*tilde, msh->args[i] + 1);
			closedir(dp);
			return (1);
		}
	}
	closedir(dp);
	return (0);
}

static int	get_tilde(t_msh *msh, char **tilde, size_t i)
{
	if (msh->args[i][1] == '-')
	{
		*tilde = env_getvalue(msh->env, "OLDPWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else if (msh->args[i][1] == '+')
	{
		*tilde = env_getvalue(msh->env, "PWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else
	{
		*tilde = env_getvalue(msh->env, "HOME=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 1);
	}
	return (1);
}

static size_t	check_tilde(char *str)
{
	size_t	i;

	i = 1;
	if (!str[i])
		return (1);
	if (str[i] == '+' || str[i] == '-' || str[i] == '/')
		return (1);
	if (ft_isalpha(str[i]))
		return (2);
	return (0);
}

void	tilde(t_msh *msh, size_t i)
{
	char	*tilde;
	size_t	status;

	status = check_tilde(msh->args[i]);
	if (status)
	{
		if (status == 1 && get_tilde(msh, &tilde, i))
		{
			ft_strdel(&msh->args[i]);
			msh->args[i] = tilde;
		}
		else if (status == 2 && get_user(msh, &tilde, i))
		{
			ft_strdel(&msh->args[i]);
			msh->args[i] = tilde;
		}
	}
}
