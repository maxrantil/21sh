/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:23:14 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/19 13:55:29 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	getenv_check(char **content, char **env_name, t_shell *sh)
{
	char	*tmp;

	tmp = env_getvalue(sh->env, *env_name);
	if (tmp)
		*content = ft_strdup(tmp);
	else
		*content = ft_strdup("");
	ft_strdel(&tmp);
	ft_strdel(env_name);
}

void	fill_env(char **tmp, t_dollar *dol, char *str, t_shell *sh)
{
	*tmp = get_full_env_name(str);
	dol->env_len = ft_strlen(*tmp);
	getenv_check(&(dol->content), tmp, sh);
}
