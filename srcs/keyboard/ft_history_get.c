/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:41:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * ft_history_get - Reads the command history from the history file and stores
 * it in a vector.
 * @t: Pointer to a t_term structure containing information about the terminal.
 *
 * This function opens the history file (creating it if necessary) and reads
 * each line of the file using the get_next_line function. It then pushes each
 * line onto a vector, which is stored in the t_term structure pointed to
 * by @t. Finally, the function closes the history file and frees any
 * memory allocated for the buffer used to read the lines.
 */
void	ft_history_get(t_term *t)
{
	char	*buf;
	int		fd;

	vec_new(&t->v_history, 0, sizeof(char) * 1024);
	t->history_file = ft_history_file_get();
	fd = open(t->history_file, O_RDWR | O_CREAT, 0644);
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
}
