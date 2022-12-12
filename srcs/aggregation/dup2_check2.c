/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_check2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:23:53 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/12 12:29:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	dup2_check2(int file_fd, int old_fd)
{
	int	dup2_fd;

	dup2_fd = dup2(file_fd, old_fd);
	if (dup2_fd == -1)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putnbr_fd(file_fd, 2);
		ft_putstr_fd(": Bad file descriptor\n", 2);
	}
	return (dup2_fd);
}
