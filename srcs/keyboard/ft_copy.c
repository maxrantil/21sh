/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:38:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:38:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It copies the word before the cursor to the clipboard
 *
 * @param t The term structure
 */
void	ft_copy(t_term *t)
{
	ssize_t	i;
	ssize_t	j;

	if (t->bytes)
	{
		i = t->index - 1;
		while (i && ft_isspace(&t->inp[i]))
			i--;
		j = i;
		while (j && !ft_isspace(&t->inp[j]))
			j--;
		if (ft_isspace(&t->inp[j]))
			j++;
		if (t->clipboard.buff)
			ft_strdel(&t->clipboard.buff);
		t->clipboard.buff = ft_strsub(&t->inp[j], 0, (size_t)((i - j) + 1));
		t->clipboard.type = COPY;
	}
}
