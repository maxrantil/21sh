/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:52 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:39:53 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It copies the current input into a buffer, pushes the current input into
 * the history vector, and sets the current row to the history row
 *
 * @param t the term structure
 */
static void	ft_history_push(t_term *t)
{
	if (t->history_row == -1)
	{
		t->input_cpy = ft_strsub(t->nl_addr[t->c_row], 0, \
		ft_strlen(t->nl_addr[t->c_row]));
		if (*t->history_buff)
		{
			ft_nl_removal(t);
			vec_push(&t->v_history, t->history_buff);
			ft_memset((void *)t->history_buff, '\0', \
			ft_strlen(t->history_buff));
		}
		t->history_row = t->c_row;
	}
	t->c_row = t->history_row;
}

/**
 * It updates the current
 * input line with the history line
 *
 * @param t the term structure
 * @param history the history string to be copied into the input line
 */
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
			ft_memcpy(t->nl_addr[t->c_row], \
			t->input_cpy, ft_strlen(t->input_cpy));
	}
}

/**
 * It clears the line from the cursor to the end of the screen
 *
 * @param t the term structure
 * @param row the row number of the line to be cleared
 */
static void	ft_history_clear_line(t_term *t, ssize_t row)
{
	// ft_setcursor(0, (t->start_row + t->history_row));
	if (row > t->history_row)
	{
		ft_setcursor(0, ft_get_linenbr() - (row - t->history_row));
		while (row > t->history_row)
		{
			ft_remove_nl_addr(t, row);
			t->total_row--;
			row--;
		}
	}
	else
		ft_setcursor(0, ft_get_linenbr());
	ft_run_capability("cd");
}

/**
 * It takes the current input, pushes it to the history, then replaces
 * the current input with the history entry
 *
 * @param t The terminal structure
 * @param his The history number to be retrieved.
 *
 * @return the address of the first element of the array.
 */
void	ft_history_trigger(t_term *t, ssize_t his)
{
	ssize_t	row;
	char	*history;

	if (t->c_row != t->total_row)
		return ;
	row = t->c_row;
	ft_history_push(t);
	ft_run_capability("vi");
	history = (char *)vec_get(&t->v_history, t->v_history.len - (size_t)his);
	ft_history_clear_line(t, row);
	ft_history_inp_update(t, history);
	ft_history_reset_nl(t, t->nl_addr[t->history_row]);
	// ft_history_clear_line(t, row);
	ft_quote_flag_reset(t);
	if (t->start_row + t->total_row >= t->ws_row)
		t->start_row = t->ws_row - (t->total_row + 1);
	ft_print_input(t, t->c_row, 1);
	if (!history)
	{
		t->history_row = -1;
		ft_strdel(&t->input_cpy);
	}
	ft_run_capability("ve");
}
