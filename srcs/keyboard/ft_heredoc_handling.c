/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:57:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:41:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It checks if the user is
 * currently typing a heredoc, and if so, it sets the `t->heredoc` variable to 1
 *
 * @param t the term structure
 */
void	ft_heredoc_handling(t_term *t)
{
	if (t->index > 2 && t->ch == '<' && !(t->q_qty % 2))
	{
		if (t->inp[t->index - 1] == '<' && t->inp[t->index - 2] != '<')
			t->heredoc = 1;
		else
			t->heredoc = 0;
	}
}
