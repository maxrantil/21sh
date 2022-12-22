/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:03 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 12:47:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It's called at the end of the main loop, and it handles the newline
 * character, the history, and the
 * input copy
 *
 * @param t the term struct
 */
void	ft_end_cycle(t_term *t)
{
	char	*tmp;

	t->start_row = ft_get_linenbr();
	if (t->bytes)
	{
		ft_memcpy(t->history_buff, t->inp, t->bytes);
		ft_nl_removal(t);
		if (t->delim)
		{
			tmp = ft_strsub(t->inp, 0, ft_strchr(t->inp, '\n') - t->inp);
			vec_push(&t->v_history, tmp);
			ft_strdel(&tmp);
		}
		else
			vec_push(&t->v_history, t->history_buff);
		ft_strclr(t->history_buff);
	}
	if (!ft_strncmp(t->inp, "history", 7))
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
	t->sigint = 0;
}
