/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 13:15:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	reset_fds(char *terminal_name)
{
	close(0);
	open(terminal_name, O_RDWR);
	close(1);
	open(terminal_name, O_RDWR);
	close(2);
	open(terminal_name, O_RDWR);
}
