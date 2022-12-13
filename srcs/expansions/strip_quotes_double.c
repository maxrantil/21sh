/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:16:35 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 14:17:16 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	remove_backslash_update_quote(char *str, size_t *len, size_t *q2)
{
	if (str[1] == '\\' || str[1] == '\'' || str[1] == '\"')
	{
		remove_backslash(str);
		(*len)--;
		(*q2)--;
	}
}

size_t	strip_quotes_double(char **str, size_t quote1)
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
			i += update_arg_dollar(i, str, &len, &quote2);
		else if ((*str)[i] == '\\')
		{
			remove_backslash_update_quote(&(*str)[i], &len, &quote2);
			i++;
		}
		else
			i++;
	}
	ft_memmove(&((*str)[quote1]), &((*str)[quote1 + 1]), len - quote1);
	ft_memmove(&((*str)[quote2 - 1]), &((*str)[quote2]), len - quote2);
	return (quote2 - 2);
}
