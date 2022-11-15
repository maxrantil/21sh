/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_write_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:59:21 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:06:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_history_write_to_file(t_term *t)
{
	char	*file;
	size_t	cpy;
	int		fd;

	file = ft_strjoin(getenv("HOME"), "/.42sh_history");
	fd = open(file, O_WRONLY);
	if (fd)
	{
		cpy = 0;
		if (t->v_history.len > 1024)
			cpy = t->v_history.len % 1024;
		while (cpy < t->v_history.len)
		{
			ft_putendl_fd((char *)vec_get(&t->v_history, cpy), fd);
			cpy++;
		}
		close(fd);
	}
	ft_strdel(&file);
}
