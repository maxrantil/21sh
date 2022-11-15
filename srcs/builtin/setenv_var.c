/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:37:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:47:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	**setenv_var(char **env, char *key, char *value)
{
	char	**new_env;
	size_t	count;
	ssize_t	j;

	count = ft_arrlen((void **)env);
	if (!count)
		++count;
	new_env = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	j = -1;
	while (env[++j])
		new_env[j] = ft_strdup(env[j]);
	ft_arrfree((void ***)&env, count);
	new_env[j++] = ft_strjoin(key, value);
	new_env[j] = NULL;
	return (new_env);
}
