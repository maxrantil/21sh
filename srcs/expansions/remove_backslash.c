/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:14:56 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 13:59:17 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	remove_newline(char *str, size_t len)
{
	ft_memmove(str, &str[2], len - 1);
	return (-1);
}

ssize_t	remove_backslash(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[1] == '\n')
		return (remove_newline(str, len));
	else if (str[1] == '\\' || str[1] == '\'' || str[1] == '\"')
	{
		ft_memmove(str, &str[1], len);
		return (0);
	}
	else
	{
		ft_memmove(str, &str[1], len);
		return (-1);
	}
}
