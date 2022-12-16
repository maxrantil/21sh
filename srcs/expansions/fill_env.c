/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:23:14 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 13:15:04 by rvuorenl         ###   ########.fr       */
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

static void	getenv_check(char **content, char **env_name, t_shell *sh)
{
	char	*tmp;

	tmp = env_getvalue(sh->env, *env_name);
	if (tmp)
		*content = ft_strdup(tmp);
	else
		*content = ft_strdup("");
	ft_strdel(env_name);
}

void	fill_env(char **tmp, t_dollar *dol, char *str, t_shell *sh)
{
	// printf("FILL_ENV\n");
	*tmp = get_full_env_name(str);
	// printf("\tenv_name (%s), ", *tmp);
	dol->env_len = ft_strlen(*tmp);
	getenv_check(&(dol->content), tmp, sh);
	// printf("content (%s)\n", dol->content);
}
