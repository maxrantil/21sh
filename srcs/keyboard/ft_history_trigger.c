/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:52 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/09 12:37:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It copies the contents of the current input buffer into the history buffer
 *
 * @param t the term structure
 * @param dst the destination string
 * @param src the string to copy
 */
static void	ft_historycpy(t_term *t, char *dst, char *src)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(t->inp);
	while (src && src[++i] && (len + i) < (MAX_HISTORY - 1))
		dst[i] = src[i];
}

/*
 * It updates the current
 * input line with the history line
 *
 * @param t the term structure
 * @param history the history string to be copied into the input line
 */
static void	ft_history_inp_update(t_term *t, char *history)
{
	ft_strclr(t->nl_addr[t->c_row]);
	if (history)
		ft_historycpy(t, t->nl_addr[t->c_row], history);
	else if (t->input_cpy)
		ft_historycpy(t, t->nl_addr[t->c_row], t->input_cpy);
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

/*
 * It copies the current line
 * into a buffer, then it adds the current line to the history, then it sets the
 * current row to the history row
 *
 * @param t the term structure
 */
static void	ft_history_push(t_term *t)
{
	ft_run_capability("vi");
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

/*
 * It takes the current row, pushes the current input to the history, then clears
 * the current line,
 * updates the input with the history, resets the newline address, resets the
 * quote flag, prints the
 * input, and then deletes the history if it's empty
 *
 * @param t the term structure
 * @param pos The position of the history to be retrieved.
 *
 * @return the address of the first character of the string.
 */
void	ft_history_trigger(t_term *t, ssize_t pos)
{
	ssize_t	row;
	char	*history;

	if (t->c_row != t->total_row)
		return ;
	row = t->c_row;
	ft_history_push(t);
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
	ft_memdel((void *)&history);
	ft_run_capability("ve");
}
