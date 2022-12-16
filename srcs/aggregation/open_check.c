/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:30:15 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 18:33:50 by rvuorenl         ###   ########.fr       */
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
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(filename, 2);
		sh_error_print(filename, 7);
	}
	return (file_fd);
}
