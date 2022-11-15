/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 15:35:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*change_shlvl(char *shlvl)
{
	int		lvl;
	char	*str_lvl;
	char	*ret;

	lvl = ft_atoi(ft_strchr(shlvl, '=') + 1);
	if (lvl <= 999)
		++lvl;
	else
		lvl = 1;
	str_lvl = ft_itoa(lvl);
	ret = ft_strdup("SHLVL=");
	ret = ft_strupdate(ret, str_lvl);
	ft_strdel(&str_lvl);
	return (ret);
}

static size_t	env_arrlen(char **arr)
{
	size_t	len;
	ssize_t	i;

	len = 0;
	i = -1;
	while (arr[++i])
		len++;
	return (len);
}

static char	**hard_coded_env(char **env)
{
	char	cwd[MAX_PATHLEN];
	size_t	i;

	i = 0;
	env = (char **)ft_memalloc(sizeof(char *) * 5);
	env[i++] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[i++] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env[i++] = ft_strdup("SHLVL=1");
	env[i++] = ft_strdup("_=/usr/bin/env");
	env[i] = NULL;
	return (env);
}

static char	**get_env(char **env, size_t j, ssize_t i)
{
	extern char	**environ;
	size_t		len;

	if (*environ)
	{
		len = env_arrlen(environ);
		env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
		while (environ[++i])
		{
			if (!ft_strncmp(environ[i], "SHLVL=", 6))
				env[j++] = change_shlvl(environ[i]);
			else
				env[j++] = ft_strdup(environ[i]);
		}
		env[j] = NULL;
	}
	else
		env = hard_coded_env(env);
	return (env);
}

void	init(t_msh *msh, t_term *t, t_builtin **ht)
{
	ssize_t		i;
	size_t		j;

	ft_init_term(t);
	hash_init(ht);
	ft_putstr("\033[2J");
	ft_putstr("\033[H");
	ft_printf("\n{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**\n");
	ft_printf("            {blu}- {yel}2{gre}1{red}s{blu}h {yel}-\n");
	ft_printf("   {yel}made {blu}by {gre}rvourenl {red}and {yel}mrantil{blu}.");
	ft_printf("\n{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{nor}\n\n");
	ft_printf("{yel}${gre}>{nor} ");
	msh->args = NULL;
	msh->paths = NULL;
	msh->cl = NULL;
	msh->env = NULL;
	j = 0;
	i = -1;
	msh->env = get_env(msh->env, j, i);
	msh->temp_env = NULL;
	vec_new(&msh->v_temp, 0, MAX_NAME);
}
