/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trigger_nl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:37:29 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 12:15:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It scrolls down one line
 */
static void	ft_scroll_down(t_term *t)
{
	ft_run_capability("vi");
	if (t->nl_addr[t->c_row + 1])
	{
		ft_run_capability("sc");
		ft_setcursor(0, t->ws_row);
		ft_run_capability("sf");
		ft_run_capability("rc");
	}
	ft_run_capability("do");
	ft_run_capability("ve");
}

/* to the
 * buffer, and if the cursor is at the end of the line, it moves the cursor
 * to the next line
 *
 * @param t the term structure
 */
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
		{
			t->start_row--;
			ft_scroll_down(t);
		}
		if (t->nl_addr[t->c_row + 1])
			ft_reset_nl_addr(t);
		else
			ft_add_nl_last_row(t, t->inp, t->bytes);
	}
	if (t->c_col == t->ws_col)
	{
		t->c_col = 0;
		ft_setcursor(t->c_col, t->start_row + ++t->c_row);
	}
}
