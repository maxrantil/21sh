/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 15:50:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_end_cycle(t_term *t)
{
	ft_putchar('\n');
	vec_push(&t->v_history, t->inp);
	if (!ft_strcmp(t->inp, "history"))
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

t_term	*ft_input_cycle(t_term *t)
{
	/* ft_printf("{yel}${gre}>{nor} "); */
	/* write(1, PROMPT, (size_t)t->prompt_len); */
	ft_add_nl_last_row(t, 0);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint(t->ch) || t->ch == ENTER)
			ft_insertion(t);
		if (t->ch == ENTER)
		{
			if (t->inp[t->bytes - 2] != '\\' && !(t->q_qty % 2))
			{
				ft_end_cycle(t);
				return (t);
			}
		}
		else if (t->ch == CTRL_D)
		{
			if (t->index < t->bytes)
				ft_delete(t);
			if (!t->bytes)
				return (NULL);
		}
		else if (t->ch == CTRL_C)
		{
			write(1, "\n", 1);
			ft_restart_cycle(t);
			write(1, PROMPT, (size_t)t->prompt_len);
		}
		else if (t->ch == BACKSPACE && t->index)
			ft_backspace(t);
		if (t->ch == ESCAPE)
			ft_esc_parse(t);
		if (t->ch == -1)
		{
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
			return (NULL);
		}
	}
	return (NULL);
}
