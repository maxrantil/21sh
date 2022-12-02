/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:30:15 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/02 13:59:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	open_check(char *filename, int mode)
{
	int	file_fd;

	file_fd = -1;
	if (mode == REDIROVER)
		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == REDIRAPP)
		file_fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		// proper error message ?
		write(2, "Error in open_check\n", 20);
		exit(10);
	}
	return (file_fd);
}
