/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:17:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/22 11:53:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_t;

static void	sig_handler(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_t);
	if (num == SIGINT)
	{
		ft_putchar('\n');
		ft_restart_cycle(g_t);
	}
}

void	ft_init_signals(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
}
