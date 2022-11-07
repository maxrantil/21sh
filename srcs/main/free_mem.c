/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/02 10:48:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	free_table(t_builtin **ht)
{
	t_builtin	*tmp;
	int			i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (ht[i])
		{
			tmp = ht[i];
			while (tmp)
			{
				tmp = tmp->next;
				free(ht[i]);
				ht[i] = NULL;
				ht[i] = tmp;
			}
		}
		i++;
	}
}

void	free_mem(t_msh *msh, t_builtin **ht, ssize_t code)
{
	if (code == 1)
	{
		if (msh->temp_env)
		{
			msh_unsetenv(msh);
			ft_arrfree((void ***)&msh->temp_env, \
			ft_arrlen((void **)msh->temp_env));
		}
		if (msh->args)
			ft_arrfree((void ***)&msh->args, ft_arrlen((void **)msh->args));
		if (msh->paths)
			ft_arrfree((void ***)&msh->paths, ft_arrlen((void **)msh->paths));
		ft_strdel(&msh->cl);
	}
	if (code == 2)
	{
		if (msh->env)
			ft_arrfree((void ***)&msh->env, ft_arrlen((void **)msh->env));
		free_table(ht);
	}
}
