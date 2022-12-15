/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:50:39 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/15 16:11:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

pid_t	fork_wrap(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("error on fork", 2);
		exit(1);
	}
	ft_printf("FORK PID = %d\n", pid);
	return (pid);
}
