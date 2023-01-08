/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:17:38 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 15:56:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/* static void	heredoc_reset(t_term *t)
{
	if (t->delim)
	{
		ft_memcpy(t->history_buff, t->inp, t->bytes);
		ft_nl_removal(t);
		vec_push(&t->v_history, t->history_buff);
	}
	ft_strdel(&t->delim);
	t->heredoc = 0;
} */

void	ft_restart_cycle(t_term *t)
{
	t->heredoc = 0;
	ft_strdel(&t->delim);
	// heredoc_reset(t);
    t->ch = 0;
    t->his = 0;
    t->quote = 0;
    t->q_qty = 0;
    t->bytes = 0;
    t->index = 0;
    t->c_col = t->prompt_len;
    t->total_row = 0;
    t->bslash = 0;
    t->c_row = 0;
    ft_strclr(t->inp);
    ft_strclr(t->history_buff);
    t->start_row = ft_get_linenbr();
}
