/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 13:19:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It sets the cursor position
 * to the position of the character at the current index
 *
 * @param t the term structure
 */
static void	set_new_cur_pos(t_term *t)
{
	t->c_row = 0;
	while (t->nl_addr[t->c_row] \
		&& &t->inp[t->index] >= t->nl_addr[t->c_row])
		t->c_row++;
	t->c_row--;
	t->c_col = ft_get_prompt_len(t, t->c_row);
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	ft_setcursor(t->c_col, t->c_row);
}

/*
 * It resets the cursor position and prints the trail of the input string
 *
 * @param t the term structure
 */
void	ft_window_size(t_term *t)
{
	struct winsize	size;

	ft_run_capability("vi");
	if (ioctl(0, TIOCGWINSZ, &size) < 0)
		ft_putstr_fd("error: ioctl in ft_window_size()", 2);
	t->ws_col = size.ws_col;
	t->ws_row = size.ws_row;
	if (*t->inp)
	{
		t->start_row = 0;
		ft_run_capability("cl");
		ft_reset_nl_addr(t);
		ft_print_input(t, 0, 0);
		set_new_cur_pos(t);
	}
	else
		t->start_row = ft_get_linenbr();
	ft_run_capability("ve");
}
