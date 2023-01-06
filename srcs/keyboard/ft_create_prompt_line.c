/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:38:33 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 13:20:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It creates a new line for the prompt
 *
 * @param t the term structure
 * @param loc the location of the cursor in the command line
 */
void	ft_create_prompt_line(t_term *t, ssize_t loc)
{
	t->c_row++;
	t->total_row++;
	if (t->start_row + t->total_row >= t->ws_row)
	{
		ft_run_capability("sf");
		t->start_row--;
	}
	ft_setcursor(0, t->start_row + t->c_row);
	ft_printf("{gre}>{nor} ");
	t->c_col = t->m_prompt_len;
	ft_add_nl_last_row(t, t->inp, loc);
}
