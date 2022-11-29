/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 17:31:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static int	ctrl_d(t_term *t)
{
	if (!t->bytes)
		return (-1);
	if (t->index < t->bytes)
		ft_delete(t);
	if (t->heredoc && !*t->nl_addr[t->c_row])
	{
		ft_putstr("21sh: warning: here-document at line ");
		ft_putnbr(t->c_row);
		ft_putstr(" delimited by end-of-file (wanted `EOF')");
		ft_end_cycle(t);
		ft_restart_cycle(t);
		return (1);
	}
	return (0);
}

static void	ft_ctrl(t_term *t)
{
	if (t->ch == CTRL_C)
		ft_restart_cycle(t);
	else if (t->ch == CTRL_W)
		ft_cut(t);
	else if (t->ch == CTRL_U)
		ft_copy(t);
	else if (t->ch == CTRL_Y)
		ft_paste(t);
	else if (t->ch == CTRL_L)
	{
		ft_run_capability("cl");
		write(1, PROMPT, (size_t)t->prompt_len);
	}
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
			|| !ft_strcmp(t->nl_addr[t->c_row], t->delim))
		{
			ft_end_cycle(t);
			return (1);
		}
		t->bslash = 0;
	}
	return (0);
}


t_term	*ft_input_cycle(t_term *t)
{
	ft_add_nl_last_row(t, 0);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint_or_enter(t))
			return (t);
		if (t->ch == CTRL_D)
		{
			if (ctrl_d(t) == 1)
				continue ;
			if (ctrl_d(t) == -1)
				return (NULL);
		}
		ft_ctrl(t);
		ft_backspace_or_escape(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
		/* if (ft_isprint(t->ch) || t->ch == ENTER)
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
		} */
	}
	return (NULL);
}
