/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:06:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	backpace_continue(t_term *t, ssize_t row, ssize_t len)
{
	if (!t->c_col)
	{
		t->c_col = t->ws_col;
		t->c_row--;
		ft_setcursor(t->c_col, ft_get_linenbr() - 1);
	}
	else
	{
		t->c_col--;
		ft_run_capability("le");
	}
	ft_run_capability("ce");
	if (!len)
	{
		if (((t->start_row + t->c_row) + 1) >= t->ws_row)
		{
			ft_run_capability("sc");
			ft_run_capability("ho");
			ft_run_capability("sr");
			ft_run_capability("rc");
			ft_run_capability("do");
		}
		// if (((t->start_row + t->c_row) + 1) >= t->ws_row)
		// {
		// 	ft_setcursor(0, 0);
		// 	ft_run_capability("sr");
		// 	ft_setcursor(t->c_col, t->ws_row);
		// }
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	ft_shift_nl_addr(t, -1);
	ft_deletion_shift(t, BCK);
}

void	ft_backspace(t_term *t)
{
	ssize_t	row;
	ssize_t	len;

	if (&t->inp[t->index] == t->nl_addr[t->c_row]
		&& ft_is_prompt_line(t, t->c_row))
		return ;
	row = ft_row_lowest_line(t);
	len = ft_len_lowest_line(t, row);
	if (t->index
		&& (t->inp[t->index - 1] == D_QUO || t->inp[t->index - 1] == S_QUO))
		ft_quote_decrement(t, 1);
	backpace_continue(t, row, len);
	if (t->inp[t->index])
		ft_print_trail(t);
}
