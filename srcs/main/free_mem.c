/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/16 15:18:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	free_table(t_hash **ht)
{
	t_hash	*tmp;
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
	// // free(ht);
	// ht = NULL;
}

static void temp_handler(t_msh *msh)
{
	size_t	i;

	msh_unsetenv(NULL, msh); //put node in here later
	ft_arrfree((void ***)&msh->temp_env, \
	ft_arrlen((void **)msh->temp_env));
	if (msh->v_temp.len)
	{
		i = 0;
		while (i < msh->v_temp.len)
		{
			char *tmp = (char *)vec_get(&msh->v_temp, i);
			char *key = env_key_extract(tmp);
			msh->env = setenv_var(msh->env, key, \
			ft_strchr(tmp, '=') + 1);
			i++;
			ft_strdel(&key);
		}
		msh->v_temp.len = 0;
	}
}

void	free_mem(t_msh *msh, t_hash **ht, ssize_t code)
{
	if (code == 1)
	{
		if (msh->temp_env)
			temp_handler(msh);
		// if (msh->args)
			// ft_arrfree((void ***)&msh->args, ft_arrlen((void **)msh->args));
		if (msh->paths)
			ft_arrfree((void ***)&msh->paths, ft_arrlen((void **)msh->paths));
		// ft_strdel(&msh->cl);
	}
	if (code == 2)
	{
		if (msh->env)
			ft_arrfree((void ***)&msh->env, ft_arrlen((void **)msh->env));
		free_table(ht);
		vec_free(&msh->v_temp);
	}
}
