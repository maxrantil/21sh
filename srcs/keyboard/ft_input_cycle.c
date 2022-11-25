/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/25 14:32:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_end_cycle(t_term *t)
{

	vec_push(&t->v_history, t->inp);
	if (!ft_strcmp(t->inp, "history"))
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

t_term	*ft_input_cycle(t_term *t)
{
	ft_add_nl_last_row(t, 0);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint(t->ch) || t->ch == ENTER)
			ft_insertion(t);
		if (t->ch == ENTER)
		{
			if ((t->bytes > 1 && t->inp[t->bytes - 2] != '\\' && !(t->q_qty % 2))
				|| (t->bytes < 2 && !(t->q_qty % 2)))
			{
				ft_end_cycle(t);
				return (t);
			}
		}
		else if (t->ch == CTRL_D)
		{
			if (!t->bytes)
				return (NULL);
			if (t->index < t->bytes)
				ft_delete(t);
		}
		else if (t->ch == BACKSPACE && t->index)
			ft_backspace(t);
		if (t->ch == ESCAPE)
			ft_esc_parse(t);
		if (t->ch == -1)
		{
			ft_putendl_fd("error, ft_get_input()", STDERR_FILENO);
			return (NULL);
		}
	}
	return (NULL);
}
