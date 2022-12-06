/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_21sh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:52:53 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 14:24:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*verify_arg(t_node *n, t_shell *sh)
{
	struct stat	statbuf;
	char		*verify;
	size_t		i;

	i = 0;
	while (sh->paths[i] \
		&& n->arg[0] && n->arg[0][0] != '\0' && n->arg[0][0] != '/' \
		&& !ft_strequ(n->arg[0], ".") && !ft_strequ(n->arg[0], ".."))
	{
		verify = ft_strjoin(sh->paths[i], "/");
		verify = ft_strupdate(verify, n->arg[0]);
		if (!lstat(verify, &statbuf))
		{
			// ft_strdel(&n->arg[0]); //valgrind says not to free?????
			n->arg[0] = verify;
			return (n->arg[0]);
		}
		ft_strdel(&verify);
		i++;
	}
	return (n->arg[0]);
}

int	exec_21sh(t_node *n, t_shell *sh/* , t_hash **ht */)
{
	char	*ptr;

	if (fork_wrap() == 0)
	{
		if (n->arg[0][0] == '.')
		{
			sh->env = env_underscore(n, sh);
			execve(n->arg[0], n->arg, sh->env);
		}
		if (check_paths(sh))
		{
			ptr = n->arg[0];
			n->arg[0] = verify_arg(n, sh);
			if (!ft_strequ(n->arg[0], ptr))
			{
				sh->env = env_underscore(n, sh);
				execve(n->arg[0], n->arg, sh->env);
			}
		}
		error_print(n->arg[0], 4);
		free_mem(n, sh/* , ht */, 2);
		exit(EXIT_FAILURE);
	}
	wait(0);
	return (1);
}
