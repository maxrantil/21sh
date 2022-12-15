/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 11:54:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	hash_error_print(char *arg)
{
	ft_putstr_fd("21sh: hash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not found", 2);
	return (-1);
}

static int	verify_arg(t_node *n, t_shell *sh, int i)
{
	struct stat	statbuf;
	char		*verify;
	int			y;

	y = 0;
	while (sh->paths[y])
	{
		verify = ft_strjoin(sh->paths[y], "/");
		verify = ft_strupdate(verify, n->arg[i]);
		if (!lstat(verify, &statbuf))
		{
			ft_strdel(&n->arg[i]);
			n->arg[i] = verify;
			return (1);
		}
		ft_strdel(&verify);
		y++;
	}
	return (0);
}

//ad -r to clear the hash table
// will this leak when i unset PATH and set it many times?
int	sh_hash(t_node *n, t_shell *sh)
{
	int		i;
	int		index;
	t_hash	*tmp;

	if (!check_paths(sh))
	{
		ft_putstr_fd("21sh: hash table empty", 2);
		return (1);
	}
	i = 0;
	if (ft_strnequ(n->arg[i], "hash", 4) && !n->arg[i + 1])
		hash_print(sh->ht);
	while (n->arg[++i])
	{
		if (verify_arg(n, sh, i))
		{
			index = hash_function(n->arg[i]);
			tmp = sh->ht[index];
			{
				while (tmp && !ft_strequ(n->arg[i], tmp->program))
					tmp = tmp->next;
				if (tmp == NULL)
					init_ht_struct(sh, n->arg[i]);
			}
		}
		else
			return (hash_error_print(n->arg[i]));
	}
	return (1);
}
