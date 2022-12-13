/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:23:14 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 14:24:39 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*get_full_env_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ((ft_isalnum(var[i])) || var[i] == '_'))
		i++;
	return (ft_strsub((const char *)var, 0, (size_t)i));
}

static void	getenv_check(char **content, char *env_name)
{
	char	*tmp;

	tmp = getenv(env_name);
	if (tmp)
		*content = ft_strdup(tmp);
	else
		*content = ft_strdup("");
}

void	fill_env(char **tmp, char **cont, size_t *env_len, char *str)
{
	*tmp = get_full_env_name(str);
	*env_len = ft_strlen(*tmp);
	getenv_check(cont, *tmp);
}
