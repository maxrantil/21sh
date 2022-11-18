/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:06:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_history_get(t_term *t)
{
	char	*buf;
	char	*file;
	int		fd;

	vec_new(&t->v_history, 0, sizeof(char) * 256);
	file = ft_strjoin(getenv("HOME"), "/.42sh_history");
	fd = open(file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		buf = NULL;
		while (get_next_line(fd, &buf) > 0)
		{
			vec_push(&t->v_history, buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		close(fd);
	}
	ft_strdel(&file);
}
