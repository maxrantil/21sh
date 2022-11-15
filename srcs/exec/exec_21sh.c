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

static size_t	count_colon(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == ':')
			count++;
		str++;
	}
	return (count);
}

static int	check_paths(t_msh *msh)
{
	char	*path;
	char	*dup_paths;
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PATH=", 5))
		{
			msh->paths = (char **)ft_memalloc(sizeof(char *) * \
			(count_colon(msh->env[i]) + 1));
			dup_paths = ft_strdup(msh->env[i]);
			path = ft_strchr(dup_paths, '=') + 1;
			i = 0;
			while (path)
				msh->paths[i++] = ft_strdup(ft_strsep(&path, ":"));
			msh->paths[i] = NULL;
			ft_strdel(&dup_paths);
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*verify_arg(t_node *node, t_msh *msh)
{
	struct stat	statbuf;
	char		*verify;
	size_t		i;

	i = 0;
	while (msh->paths[i] \
		&& !ft_strequ(node->arg[0], ".") \
		&& !ft_strequ(node->arg[0], "..") \
		&& node->arg[0][0] != '\0' \
		&& node->arg[0][0] != '/')
	{
		verify = ft_strjoin(msh->paths[i], "/");
		verify = ft_strupdate(verify, node->arg[0]);
		if (!lstat(verify, &statbuf))
		{
			ft_strdel(&node->arg[0]);
			node->arg[0] = verify;
			return (node->arg[0]);
		}
		ft_strdel(&verify);
		i++;
	}
	return (node->arg[0]);
}

int	exec_21sh(t_node *node, t_msh *msh)
{
	pid_t	pid;
	int		status;
	char	*ptr;

	pid = fork();
	if (pid == 0)
	{
		if (node->arg[0][0] == '.')
			execve(node->arg[0], node->arg, msh->env);
		if (check_paths(msh))
		{
			ptr = node->arg[0];
			node->arg[0] = verify_arg(node, msh);
			if (ft_strcmp(node->arg[0], ptr))
				execve(node->arg[0], node->arg, msh->env);
		}
		error_print(node->arg[0], 4);
		free_mem(msh, NULL, 1);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putstr_fd("error: pid failed\n", STDERR_FILENO);
	else
		waitpid(pid, &status, 0);
	return (1);
}
