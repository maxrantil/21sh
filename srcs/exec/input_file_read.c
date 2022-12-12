/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:13:15 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/12 22:54:11 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	check_open_errors(char *filename)
{
	if (!access(filename, F_OK))
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

static int	open_read_check(char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		check_open_errors(filename);
	return (file_fd);
}

void	input_file_read(t_node *n, t_shell *sh)
{
	int	file_fd;

	close(0);
	file_fd = open_read_check(n->arg[1]);
	if (file_fd != -1)
		exec_tree(n->left, sh);
}
