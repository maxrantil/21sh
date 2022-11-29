/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 13:26:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	free_table(t_hash **ht)
{
	t_hash	*tmp;
	int		i;

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

static void temp_handler(t_node *n, t_shell *sh)
{
	size_t	i;

	msh_unsetenv(n, sh);
	ft_arrfree((void ***)&sh->temp_env, \
	ft_arrlen((void **)sh->temp_env));
	if (sh->v_tmp_env.len)
	{
		i = 0;
		while (i < sh->v_tmp_env.len)
		{
			char *tmp = (char *)vec_get(&sh->v_tmp_env, i);
			char *key = env_key_extract(tmp);
			sh->env = setenv_var(sh->env, key, \
			ft_strchr(tmp, '=') + 1);
			i++;
			ft_strdel(&key);
		}
		sh->v_tmp_env.len = 0;
	}
}

void	free_mem(t_node *root, t_shell *sh, t_hash **ht, ssize_t code)
{
	if (code == 1)
	{
		if (sh->temp_env)
			temp_handler(root, sh);
		if (sh->paths)
			ft_arrfree((void ***)&sh->paths, ft_arrlen((void **)sh->paths));
		// tree_print(root);k
		tree_free(root);
	}
	if (code == 2)
	{
		if (sh->env)
			ft_arrfree((void ***)&sh->env, ft_arrlen((void **)sh->env));
		free_table(ht);
		vec_free(&sh->v_tmp_env);
	}
}
