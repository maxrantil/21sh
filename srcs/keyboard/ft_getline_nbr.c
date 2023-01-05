/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:24 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/05 13:11:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It gets the current line number of the cursor
 *
 * @return The line number of the cursor.
 */
int	ft_get_linenbr(void)
{
	char	buf[BUFFSIZE];
	int		len;
	int		i;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	len = 0;
	while (read(0, buf + len, 1) == 1)
	{
		if (buf[len++] == 'R')
			break ;
	}
	len = 0;
	i = 0;
	while (buf[i] && buf[i] != ';')
	{
		if (ft_isdigit(buf[i]))
			buf[len++] = buf[i];
		i++;
	}
	buf[len] = '\0';
	return (ft_atoi(buf) - 1);
}
