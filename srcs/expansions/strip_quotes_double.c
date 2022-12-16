/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:16:35 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 15:08:17 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static ssize_t	remove_backslash_update_quote(char *st, size_t *len, size_t *q2)
{
	ssize_t	ret;

	ret = 1;
	if (st[1] == '\n')
	{
		ret += remove_backslash(st);
		(*len) -= 2;
		(*q2) -= 2;
	}
	else if (st[1] == '\\' || st[1] == '\'' || st[1] == '\"')
	{
		ret += remove_backslash(st);
		(*len)--;
		(*q2)--;
	}
	return (ret);
}

static void	update_quotes(char *str, size_t *q2, size_t *tot_len, t_shell *sh)
{
	char	*env_name;
	char	*content;
	size_t	env_len;
	size_t	cont_len;

	env_name = get_full_env_name(str);
	content = env_getvalue(sh->env, env_name);
	env_len = ft_strlen(env_name);
	cont_len = ft_strlen(content);
	*tot_len += cont_len - env_len - 1;
	*q2 += cont_len - env_len - 1;
}

size_t	strip_quotes_double(char **str, size_t quote1, t_shell *sh)
{
	size_t	i;
	size_t	quote2;
	size_t	len;

	i = quote1;
	len = ft_strlen(*str);
	quote2 = find_matching_quote(&((*str)[quote1]), (*str)[quote1]);
	quote2 += quote1;
	while (i < quote2)
	{
		if ((*str)[i] == '$')
		{
			update_quotes(&((*str)[i + 1]), &quote2, &len, sh);
			i += update_arg_dollar(i, str, sh);
		}
		else if ((*str)[i] == '\\')
			i += remove_backslash_update_quote(&(*str)[i], &len, &quote2);
		else
			i++;
	}
	ft_memmove(&((*str)[quote1]), &((*str)[quote1 + 1]), len - quote1);
	ft_memmove(&((*str)[quote2 - 1]), &((*str)[quote2]), len - quote2);
	return (quote2 - 2);
}
