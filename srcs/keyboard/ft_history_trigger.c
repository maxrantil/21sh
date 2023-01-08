/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:52 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 14:42:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_history_reset_nl(t_term *t, char *inp)
{
	ssize_t	i;
	ssize_t	col;
	ssize_t	row;

	i = -1;
	col = 0;
	row = t->c_row;
	while (inp[++i])
	{
		col++;
		if (((col + ft_get_prompt_len(t, row))) == t->ws_col || inp[i] == '\n')
		{
			row++;
			col = 0;
			t->total_row++;
			ft_add_nl_last_row(t, inp, i + 1);
		}
	}
	t->bytes = &inp[i] - t->nl_addr[0];
	t->index = t->bytes;
}

static void	ft_history_inp_update(t_term *t, char *history)
{
	if (history)
	{
		ft_memset((void *)t->nl_addr[t->c_row], '\0', \
		ft_strlen(t->nl_addr[t->c_row]));
		ft_memcpy(t->nl_addr[t->c_row], history, ft_strlen(history));
	}
	else
	{
		ft_memset((void *)t->nl_addr[t->c_row], '\0', \
		ft_strlen(t->nl_addr[t->c_row]));
		if (t->input_cpy)
			ft_memcpy(t->nl_addr[t->c_row], t->input_cpy, \
			ft_strlen(t->input_cpy));
	}
}

static void	ft_history_clear_line(t_term *t, ssize_t row)
{
	ft_setcursor(0, (t->start_row + t->history_row));
	if (row > t->history_row)
	{
		while (row > t->history_row)
		{
			ft_remove_nl_addr(t, row);
			t->total_row--;
			row--;
		}
	}
	ft_run_capability("cd");
}

static void	ft_history_push(t_term *t)
{
	if (t->history_row == -1)
	{
		t->input_cpy = ft_strsub(t->nl_addr[t->c_row], 0, \
		ft_strlen(t->nl_addr[t->c_row]));
		if (*t->history_buff)
		{
			ft_nl_removal(t);
			ft_history_add_command(t, t->history_buff);
			ft_memset((void *)t->history_buff, '\0', \
			ft_strlen(t->history_buff));
		}
		t->history_row = t->c_row;
	}
	t->c_row = t->history_row;
}

void	ft_history_trigger(t_term *t, ssize_t pos)
{
	ssize_t	row;
	char	*history;

	if (t->c_row != t->total_row)
		return ;
	row = t->c_row;
	ft_history_push(t);
	ft_run_capability("vi");
	if (t->history[t->history_size - pos])
		history = ft_strdup(t->history[t->history_size - (size_t)pos]);
	else
		history = ft_strdup("");
	ft_history_clear_line(t, row);
	ft_history_inp_update(t, history);
	ft_history_reset_nl(t, t->nl_addr[t->history_row]);
	ft_quote_flag_reset(t);
	if (t->start_row + t->total_row >= t->ws_row)
		t->start_row = t->ws_row - (t->total_row + 1);
	ft_print_input(t, t->c_row, 1);
	if (!history)
	{
		ft_strdel(&t->input_cpy);
		t->history_row = -1;
	}
	ft_run_capability("ve");
}
