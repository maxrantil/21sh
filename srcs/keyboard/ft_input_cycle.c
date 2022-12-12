/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 11:24:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static int	ft_ctrl(t_term *t)
{
	if (t->ch == CTRL_W)
		ft_cut(t);
	else if (t->ch == CTRL_U)
		ft_copy(t);
	else if (t->ch == CTRL_Y)
		ft_paste(t);
	else if (t->ch == CTRL_L)
	{
		ft_run_capability("cl");
		return (0);
	}
	return (1);
}

static void	ft_backspace_or_escape(t_term *t)
{
	if (t->ch == BACKSPACE && t->index)
		ft_backspace(t);
	if (t->ch == ESCAPE)
		ft_esc_parse(t);
}

static int	ft_isprint_or_enter(t_term *t)
{
	if (ft_isprint(t->ch) || t->ch == ENTER)
		ft_insertion(t);
	if (t->ch == ENTER)
	{
		if ((!t->bslash && !(t->q_qty % 2) && !t->delim) \
			|| ft_strequ(t->nl_addr[t->c_row], t->delim))
		{
			ft_end_cycle(t);
			return (1);
		}
		t->bslash = 0;
	}
	return (0);
}

int	ft_input_cycle(t_term *t)
{
	ft_add_nl_last_row(t, 0);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint_or_enter(t))
			return (1);
		else if (t->ch == CTRL_D)
		{
			if (!t->bytes)
				return (0);
			else if (t->index < t->bytes)
				ft_delete(t);
			else if ((t->heredoc && !*t->nl_addr[t->c_row]))
			{
				t->heredoc = 0;
				ft_end_cycle(t);
				return (-1);
			}
		}
		if (!ft_ctrl(t))
		{
			ft_restart_cycle(t);
			continue ;
		}
		ft_backspace_or_escape(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
	return (0);
}
