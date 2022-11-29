/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bslash_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:28:08 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 17:10:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * If the character is a backslash, and the index is at the end of the input,
 * and we're not in a
 * heredoc, then we check to see if the number of backslashes is odd or even.
 * If it's odd, then we set
 * the bslash flag to 1, otherwise we set it to 0
 *
 * @param t the structure that holds all the information about the current
 * state of the terminal.
 */
void	ft_bslash_handling(t_term *t)
{
	ssize_t	i;

	i = t->index - 1;
	if (t->ch == '\\' && t->index == t->bytes && !t->heredoc)
	{
		while (i && t->inp[i] == '\\')
			i--;
		if ((t->index - i) % 2)
			t->bslash = 1;
		else
			t->bslash = 0;
	}
	else
		if (t->ch != D_QUO && t->ch != S_QUO)
			t->bslash = 0;
}
