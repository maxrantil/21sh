/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 13:05:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It reads the history file and stores it in a vector
 *
 * @param t the terminal structure
 */
void	ft_history_get(t_term *t)
{
	char	*buf;
	int		fd;

	t->history = (char **)ft_memalloc(sizeof(char *) * MAX_HISTORY + 1);
	t->history_file = ft_history_file_get();
	fd = open(t->history_file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		buf = NULL;
		i = 0;
		while (get_next_line(fd, &buf) > 0)
		{
			t->history[t->history_size++] = ft_strdup(buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		t->history[t->history_size] = NULL;
		close(fd);
	}
}
