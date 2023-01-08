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
	TEST: getcwd failure
*/
static char	*get_file(void)
{
	char	cwd[MAX_PATH];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, "/.42sh_history"));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, "/.42sh_history"));
}

static void	count_history(t_term *t)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	size = 0;
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			size++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
	t->history_size = size;
}

void	ft_history_get(t_term *t)
{
	char	*line;
	int		fd;
	int		i;

	t->history_file = get_file();
	count_history(t);
	t->history = (char **)malloc(sizeof(char *) * (t->history_size + 1));
	ft_bzero(t->history, t->history_size + 1);
	i = 0;
	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			t->history[i] = ft_strdup(line);
			i++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		t->history[i] = NULL;
		t->history_size = i;
	}
}
