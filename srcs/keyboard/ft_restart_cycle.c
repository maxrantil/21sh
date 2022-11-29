/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:17:38 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:18:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_restart_cycle(t_term *t)
{
	ft_printf("{yel}${gre}>{nor} ");
	ft_strclr(t->inp);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->heredoc = 0;
	t->c_col = t->prompt_len;
	t->start_row = ft_get_linenbr();
	t->total_row = 0;
	t->his = 0;
	t->c_row = t->total_row;
	ft_strdel(&t->delim);
	ft_setcursor(t->c_col, t->c_row + t->start_row);
}
