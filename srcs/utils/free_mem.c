/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 11:51:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term	*g_t;

static void	free_ht(t_hash **ht)
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
				ft_strdel(&tmp->program);
				ft_memdel((void **)tmp);
				tmp = tmp->next;
			}
		}
		i++;
	}
}

static void	temp_handler(t_node *n, t_shell *sh)
{
	char	*tmp;
	char	*key;
	size_t	i;

	sh_unsetenv(n, sh);
	ft_arrfree((void ***)&sh->temp_env, \
	ft_arrlen((void **)sh->temp_env));
	if (sh->v_tmp_env.len)
	{
		i = 0;
		while (i < sh->v_tmp_env.len)
		{
			tmp = (char *)vec_get(&sh->v_tmp_env, i);
			key = env_key_extract(tmp);
			sh->env = setenv_var(sh->env, key, \
			ft_strchr(tmp, '=') + 1);
			i++;
			ft_strdel(&key);
		}
		sh->v_tmp_env.len = 0;
	}
}

static void	code_less_then_three(t_node *root, t_shell *sh, ssize_t code)
{
	if (sh->temp_env)
		temp_handler(root, sh);
	if (sh->paths)
		ft_arrfree((void ***)&sh->paths, ft_arrlen((void **)sh->paths));
	if (sh->cl)
		tree_free(root);
	ft_memdel((void **)&sh->cl);
	reset_fds(sh->term_name);
	if (code == 2)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->raw);
	if (code == 1 && !g_t->sigint)
		ft_printf("{yel}${gre}>{nor} ");
	ft_restart_cycle(g_t);
	g_t->sigint = 0;
}

static void	code_is_three(t_shell *sh)
{
	if (sh->env)
		ft_arrfree((void ***)&sh->env, ft_arrlen((void **)sh->env));
	free_ht(sh->ht);
	vec_free(&sh->v_tmp_env);
	ft_history_write_to_file(g_t);
	ft_disable_raw_mode(sh);
}

void	free_mem(t_node *root, t_shell *sh, ssize_t code)
{
	if (code < 3)
		code_less_then_three(root, sh, code);
	if (code == 3)
		code_is_three(sh);
}
