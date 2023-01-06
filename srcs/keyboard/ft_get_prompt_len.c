/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:19 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 13:04:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the prompt length of the given row
 *
 * @param t the term structure
 * @param row the row of the cursor
 *
 * @return The length of the prompt.
 */
ssize_t	ft_get_prompt_len(t_term *t, ssize_t row)
{
	if (!row)
		return (t->prompt_len);
	if (t->nl_addr[row][-1] == '\n')
		return (t->m_prompt_len);
	return (0);
}
