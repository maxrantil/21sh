/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 14:33:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It takes a 2d array of strings, and pushes each string into a vector
 *
 * @param t the term struct
 * @param buf_2d a 2d array of strings, each string is a line of the file
 */
void	push_to_history(t_term *t, char ***buf_2d)
{
	int	buf_size;

	vec_new(&t->v_history, 0, sizeof(char) * BUFF_SIZE + 1);
	buf_size = -1;
	while ((*buf_2d)[++buf_size])
		vec_push(&t->v_history, (*buf_2d)[buf_size]);
	buf_size = -1;
	while ((*buf_2d)[++buf_size])
		ft_strdel(&(*buf_2d)[buf_size]);
	free(*buf_2d);
}

/*
 * It reads the history file and stores it in a vector
 *
 * @param t the terminal structure
 */
void	ft_history_get(t_term *t)
{
	char	*buf;
	char	**buf_2d;
	int		fd;
	int		buf_size;

	buf_2d = (char **)ft_memalloc(sizeof(char *) * 1048 + 1);
	t->history_file = ft_history_file_get();
	fd = open(t->history_file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		buf = NULL;
		buf_size = 0;
		while (get_next_line(fd, &buf) > 0)
		{
			buf_2d[buf_size++] = ft_strdup(buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		buf_2d[buf_size] = NULL;
		push_to_history(t, &buf_2d);
		close(fd);
	}
}
