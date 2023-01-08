/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_write_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:59:21 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/21 10:36:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It writes the history to the file
 *
 * @param t The terminal structure.
 */
void	ft_history_write_to_file(t_term *t)
{
	int		cpy;
	int		fd;

	fd = open(t->history_file, O_WRONLY | O_TRUNC);
	if (fd)
	{
		cpy = 0;
		if (t->history_size > MAX_HISTORY)
			cpy = t->history_size % MAX_HISTORY;
		while (cpy < t->history_size)
		{
			ft_putendl_fd((char *)t->history[cpy], fd);
			cpy++;
		}
		close(fd);
	}
}
