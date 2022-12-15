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

static int	verify_arg(t_node *n, t_shell *sh)
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
			ft_strdel(&n->arg[0]); //valgrind says not to free?????
			n->arg[0] = verify;
			return (1);
		}
		ft_strdel(&verify);
		i++;
	}
	return (0);
}

static int does_program_need_raw(t_node *n)
{
	if (n->arg[0] && (ft_strstr(n->arg[0], "bash")
		|| ft_strstr(n->arg[0], "vi")
		|| ft_strstr(n->arg[0], "emacs")))
		return (1);
	return (0);
}

static void	need_raw_mode(t_node *n, t_shell *sh, int mode)
{
	if (mode == 1)
	{
		if (does_program_need_raw(n))
			ft_disable_raw_mode(sh);
	}
	else
	{
		if (does_program_need_raw(n))//try TCSANOW and see if it doest return -1
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->raw); //might need to have a discussion with Alex about this, why does it work and also why does is give back -1 (errror) when it works
	}
}

int	exec_21sh(t_node *n, t_shell *sh)
{
	need_raw_mode(n, sh, 1);
	if (fork_wrap() == 0)
	{
		if (n->arg[0][0] == '.' || n->arg[0][0] == '/')
		{
			sh->env = env_underscore(n, sh);
			execve(n->arg[0], n->arg, sh->env);
		}
		if (check_paths(sh))
		{
			if (verify_arg(n, sh))
			{
				sh->env = env_underscore(n, sh);
				execve(n->arg[0], n->arg, sh->env);
			}
		}
		sh_error_print(n->arg[0], 4);
		free_mem(n, sh, 2);
		exit(EXIT_FAILURE);
	}
	wait(0);
	need_raw_mode(n, sh, 0);
	return (1);
}
