/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:38:53 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 14:19:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It checks if the character at the given index is a backslash, a double
 * quote, a single quote, or a less than sign. If it's a backslash, it sets
 * the `bs` variable to 1. If it's a less than sign, it
 * sets the `hd` variable to 1. If it's a double quote or a single quote, it
 * checks if the character is escaped by a backslash. If it is, it returns 1.
 * Otherwise, it returns 0
 *
 * @param t the term structure
 * @param index the index of the current character in the input string
 * @param bs backslash
 * @param hd is a flag that indicates if the current character is a '<'
 */
static int	ft_inhibitor_catch(t_term *t, ssize_t index, int *bs, int *hd)
{
	*bs = 0;
	*hd = 0;
	if (t->inp[index] == '<')
		*hd = 1;
	else if (t->inp[index] == '\\')
		*bs = 1;
	else if ((t->inp[index] == D_QUO || t->inp[index] == S_QUO) \
	&& !ft_bslash_escape_check(t, index))
		return (1);
	return (0);
}

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, ssize_t index)
{
	int	blash;
	int	quote;
	int	heredoc;

	quote = ft_inhibitor_catch(t, index, &blash, &heredoc);
	t->inp[index] = '\0';
	while (&t->inp[index] < &t->inp[t->bytes])
	{
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index + 1] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		index++;
	}
	t->bytes--;
	if (blash)
		ft_quote_flag_check(t, t->index);
	else if (heredoc)
	{
		ft_heredoc_handling(t);
		if (!t->heredoc && t->delim)
			ft_strdel(&t->delim);
	}
	else if (quote)
		ft_quote_flag_reset(t);
}
