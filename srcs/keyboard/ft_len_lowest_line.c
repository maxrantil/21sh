/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_lowest_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:17:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 16:17:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

ssize_t	ft_len_lowest_line(t_term *t, ssize_t row)
{
	ssize_t	len;

	if (t->nl_addr[row + 1])
		len = t->nl_addr[row + 1] - t->nl_addr[row];
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	if (ft_is_prompt_line(t, row))
	{
		if (!row)
			len += t->prompt_len;
		else
			len += t->m_prompt_len;
	}
	return (len);
}