/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:14:56 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 14:15:08 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	remove_backslash(char *str)
{
	size_t	len;

	if (str[1] == '\\' || str[1] == '\'' || str[1] == '\"')
	{
		len = ft_strlen(str);
		ft_memmove(str, &str[1], len);
	}
}
