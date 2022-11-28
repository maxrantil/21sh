/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:59:17 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/28 22:22:25 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	reset_fd(void)
{
	int	fd;

	close(0);
	fd = open("/dev/fd/0", O_RDWR);
	close(1);
	fd = open("/dev/fd/1", O_RDWR);
	close(2);
	fd = open("/dev/fd/2", O_RDWR);
}
