/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:14:56 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 13:39:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	remove_newline(char *str, size_t len)
{
	ft_memmove(str, &str[2], len - 1);
	return (-1);
}

int	remove_backslash(char *str)
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

//		memmove should be from the second \, so it applies also on \ \n

// 0123 4567
// abc\\ndef
// abcdef
// abc\def
// abc\\def
