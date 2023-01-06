/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_lowest_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:40:19 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 13:45:05 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the length of the line at the given row
 *
 * @param t the term structure
 * @param row the row of the cursor
 *
 * @return The length of the lowest line.
 */
ssize_t	ft_len_lowest_line(t_term *t, ssize_t row)
{
	ssize_t	len;

	if (t->nl_addr[row + 1])
		len = t->nl_addr[row + 1] - t->nl_addr[row] - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	len += ft_get_prompt_len(t, row);
	return (len);
}
