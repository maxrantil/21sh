/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:38:38 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:38:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It handles the control keys
 *
 * @param t the term structure
 */
void	ft_ctrl(t_term *t)
{
	if (t->ch == CTRL_W)
		ft_cut(t);
	else if (t->ch == CTRL_U)
		ft_copy(t);
	else if (t->ch == CTRL_Y)
		ft_paste(t);
	else if (t->ch == CTRL_L)
	{
		t->start_row = 0;
		ft_run_capability("vi");
		ft_run_capability("cl");
		ft_print_input(t, 0, 0);
		ft_run_capability("ve");
		// ft_restart_cycle(t);
	}
}
