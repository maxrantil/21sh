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

static char	**set_tempenv(t_node *node, t_msh *msh, size_t len)
{
	char	**temp_env;
	size_t	i;

	temp_env = NULL;
	i = 1;
	if (!msh->cl)
	{
		if (len)
		{
			temp_env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
			i = 0;
			while (i++ < len)
				temp_env[i - 1] = ft_strdup(node->arg[i]);
			temp_env[i - 1] = NULL;
		}
	}
	return (temp_env);
}

static int	env_heart(t_node *node, t_msh *msh, size_t arglen)
{
	size_t	i;
	char	**temp_args;

	i = 0;
	while (node->arg[++i] && ft_strchr(node->arg[i], '='))	//make more checks for invalid input, like =, =a, a=, a=,staring with only char or '_' or key=NULL
		setenv_loop(msh, node->arg[i], 1);
	msh->temp_env = set_tempenv(node, msh, i - 1);
	if (i < arglen)
	{
		// msh->arg = switch_args(node->arg, arglen, i);
		int y = 0;
		while (node->arg[y])
			ft_strclr(node->arg[y++]);
		temp_args = switch_args(node->arg, arglen, i);
		y = -1;
		while (temp_args[++y])
			node->arg[y] = ft_strdup(temp_args[y]);
		exec_21sh(node, msh);
		return (1);
	}
	return (0);
}

int	msh_env(t_node *node, t_msh *msh)
{
	size_t	i;
	size_t	arglen;

	arglen = ft_arrlen((void **)node->arg);
	if (arglen > 1)
	{
		if (env_heart(node, msh, arglen))
			return (1);
	}
	if (*msh->env)
	{
		i = 0;
		while (msh->env[i])
			ft_printf("%s\n", msh->env[i++]);
	}
	else
		ft_printf("minishell: env: environment is empty\n");
	return (1);
}
