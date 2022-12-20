/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:40:56 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:40:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It pastes the contents of the clipboard into the input buffer
 *
 * @param t The term structure.
 */
void	ft_paste(t_term *t)
{
	int		i;

	i = -1;
	if (t->clipboard.buff)
	{
		ft_run_capability("vi");
		while (t->bytes < BUFFSIZE && t->clipboard.buff[++i])
		{
			t->c_col++;
			ft_putc(t->clipboard.buff[i]);
			ft_shift_nl_addr(t, 1);
			if (t->inp[t->index])
				ft_shift_insert(t);
			t->inp[t->index++] = t->clipboard.buff[i];
			t->bytes++;
			ft_trigger_nl(t);
			if (t->c_col == t->ws_col)
				t->c_row++;
		}
		if (t->inp[t->index])
			ft_print_trail(t);
		if (t->clipboard.type == CUT)
			ft_strdel(&t->clipboard.buff);
		ft_run_capability("ve");
	}
}
