/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/06 17:00:53 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*verify_arg(t_node *n, t_shell *sh, int i)
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
			// ft_strdel(&n->arg[0]); //valgrind says not to free?????
			n->arg[i] = verify;
			return (n->arg[i]);
		}
		ft_strdel(&verify);
		y++;
	}
	return (n->arg[i]);
}

int	sh_hash(t_node *n, t_shell *sh) //ad -r to clear the hash table
{
	int		i;
	char	*ptr;

	if (!check_paths(sh)) // will this leak when i unset PATH and set it many times?
	{
		ft_putstr_fd("21sh: hash table empty", 2);
		return (1);
	}
	i = 0;
	if (ft_strnequ(n->arg[i], "hash", 4) && !n->arg[i + 1])
		hash_print(sh->ht);
	while (n->arg[++i])
	{
		ptr = n->arg[i];
		n->arg[i] = verify_arg(n, sh, i);
		if (!ft_strequ(n->arg[i], ptr))
			init_ht_struct(sh, n->arg[i]);
		else
		{
			ft_putstr_fd("21sh: hash: ", 2);
			ft_putstr_fd(n->arg[i], 2);
			ft_putstr_fd(": not found", 2);
			return (-1);
		}
	}
	return (1);
}
