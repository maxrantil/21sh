/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:37:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:47:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	**unset_env_var(char **env, char *key)
{
	char	**new_env;
	size_t	count;
	size_t	i;
	size_t	j;

	count = ft_arrlen((void **)env);
	new_env = (char **)ft_memalloc(sizeof(char *) * count);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)))
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_arrfree((void ***)&env, count);
	return (new_env);
}
