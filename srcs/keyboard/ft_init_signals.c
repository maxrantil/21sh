/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:17:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 12:04:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_t;

/*
 * It's a signal handler that
 * handles the window size change and the interrupt signal
 *
 * @param num The signal number.
 */
void	sig_handler(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_t);
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		ft_restart_cycle(g_t);
		ft_printf("{yel}${gre}>{nor} ");
		g_t->sigint = 1;
	}
}

/*
 * It initializes the signal handlers for the program
 */
void	ft_init_signals(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);

}