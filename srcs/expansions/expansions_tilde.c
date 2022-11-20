/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 18:09:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_user(t_node *n, char **tilde, size_t i)
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
		if (!ft_strncmp(dirp->d_name, (const char *)&n->arg[i][1], len))
		{
			*tilde = ft_strdup("/Users/");
			*tilde = ft_strupdate(*tilde, n->arg[i] + 1);
			closedir(dp);
			return (1);
		}
	}
	closedir(dp);
	return (0);
}

static int	get_tilde(t_node *n, t_shell *sh, char **tilde, size_t i)
{
	if (n->arg[i][1] == '-')
	{
		*tilde = env_getvalue(sh->env, "OLDPWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, n->arg[i] + 2);
	}
	else if (n->arg[i][1] == '+')
	{
		*tilde = env_getvalue(sh->env, "PWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, n->arg[i] + 2);
	}
	else
	{
		*tilde = env_getvalue(sh->env, "HOME=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, n->arg[i] + 1);
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

void	expansions_tilde(t_node *n, t_shell *sh, size_t i)
{
	char	*tilde;
	size_t	status;

	status = check_tilde(n->arg[i]);
	if (status)
	{
		if (status == 1 && get_tilde(n, sh, &tilde, i))
		{
			ft_strdel(&n->arg[i]);
			n->arg[i] = tilde;
		}
		else if (status == 2 && get_user(n, &tilde, i))
		{
			ft_strdel(&n->arg[i]);
			n->arg[i] = tilde;
		}
	}
}
