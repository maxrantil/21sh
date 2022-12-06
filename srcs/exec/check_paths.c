/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:08:13 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/06 15:10:37 by mrantil          ###   ########.fr       */
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

int	check_paths(t_shell *sh)
{
	char	*path;
	char	*dup_paths;
	size_t	i;

	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], "PATH=", 5))
		{
			sh->paths = (char **)ft_memalloc(sizeof(char *) * \
			(count_colon(sh->env[i]) + 1));
			dup_paths = ft_strdup(sh->env[i]);
			path = ft_strchr(dup_paths, '=') + 1;
			i = 0;
			while (path)
				sh->paths[i++] = ft_strdup(ft_strsep(&path, ":"));
			sh->paths[i] = NULL;
			ft_strdel(&dup_paths);
			return (1);
		}
		i++;
	}
	return (0);
}
