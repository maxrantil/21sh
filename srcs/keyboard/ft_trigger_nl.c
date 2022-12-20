/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trigger_nl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:37:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:37:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It scrolls down one line
 */
static void	ft_scroll_down(void)
{
	ft_run_capability("sc");
	ft_run_capability("sf");
	ft_run_capability("rc");
	ft_run_capability("do");
}

void	ft_trigger_nl(t_term *t)
{
	ssize_t	len;
	ssize_t	row;

	row = ft_row_lowest_line(t);
	len = ft_len_lowest_line(t, row);
	if (len == t->ws_col)
	{
		t->total_row++;
		if ((t->start_row + t->total_row) >= t->ws_row)
			ft_scroll_down();
		if (t->nl_addr[t->c_row + 1])
			ft_reset_nl_addr(t);
		else
			ft_add_nl_last_row(t, t->inp, t->bytes);
	}
	if (t->c_col == t->ws_col)
	{
		t->c_col = 0;
		t->c_row++;
		ft_run_capability("do");
	}
}
