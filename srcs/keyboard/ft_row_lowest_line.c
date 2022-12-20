/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_row_lowest_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:42:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:42:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the row number of the lowest line in the terminal
 *
 * @param t the terminal structure
 *
 * @return The row of the lowest line in the terminal.
 */
ssize_t	ft_row_lowest_line(t_term *t)
{
	ssize_t	row;

	row = t->c_row;
	while (t->nl_addr[row + 1] && !ft_is_prompt_line(t, row + 1))
		row++;
	return (row);
}
