/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:06:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	set_new_cur_pos(t_term *t)
{
	while (t->nl_addr[t->c_row] \
	&& &t->inp[t->index] >= t->nl_addr[t->c_row])
		t->c_row++;
	t->c_row--;
	t->c_col = 0;
	if (ft_is_prompt_line(t, t->c_row))
	{
		if (!t->c_row)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
	}
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	ft_setcursor(t->c_col, t->c_row + t->start_row);
}

void	ft_window_size(t_term *t)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
	{
		ft_putstr_fd("ioctl error", 2);
		exit(1);
	}
	t->ws_col = size.ws_col;
	t->ws_row = size.ws_row;
	if (*t->inp)
	{
		t->quote = 0;
		t->q_qty = 0;
		ft_reset_nl_addr(t);
		t->c_row = 0;
		set_new_cur_pos(t);
		ft_print_trail(t);
	}
}
