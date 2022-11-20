/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 17:23:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	**switch_args(char **args, size_t arglen, size_t i)
{
	char	**new_args;
	size_t	j;

	new_args = \
	(char **)ft_memalloc(sizeof(char *) * (arglen - i + 1));
	j = 0;
	while (args[i])
		new_args[j++] = ft_strdup(args[i++]);
	new_args[j] = NULL;
	ft_arrfree((void ***)&args, arglen);
	return (new_args);
}

static char	**set_tempenv(t_node *n, t_shell *sh, size_t len)
{
	char	**temp_env;
	size_t	i;

	temp_env = NULL;
	(void)sh;
	i = 1;
	if (len)
	{
		temp_env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
		i = 0;
		while (i++ < len)
			temp_env[i - 1] = ft_strdup(n->arg[i]);
		temp_env[i - 1] = NULL;
	}
	return (temp_env);
}

static int	env_heart(t_node *n, t_shell *sh, size_t arglen)
{
	size_t	i;

	i = 0;
	while (n->arg[++i] && ft_strchr(n->arg[i], '='))	//make more checks for invalid input, like =, =a, a=, a=,staring with only char or '_' or key=NULL
		setenv_loop(sh, n->arg[i], 1);
	sh->temp_env = set_tempenv(n, sh, i - 1);
	if (i < arglen)
	{
		n->arg = switch_args(n->arg, arglen, i);
		exec_21sh(n, sh, NULL);
		return (1);
	}
	return (0);
}

int	msh_env(t_node *n, t_shell *sh)
{
	size_t	i;
	size_t	arglen;

	arglen = ft_arrlen((void **)n->arg);
	if (arglen > 1)
	{
		if (env_heart(n, sh, arglen))
			return (1);
	}
	if (*sh->env)
	{
		i = 0;
		while (sh->env[i])
			ft_putendl(sh->env[i++]);
	}
	else
		ft_putendl_fd("21sh: env: environment is empty", 2);
	return (1);
}
