/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:42:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It prints the history of the shell
 *
 * @param t the terminal structure
 */
void	ft_history(t_term *t)
{
	int		i;

	i = 0;
	while (t->history[i])
	{
		ft_printf("%4d %s", i, t->history[i]);
		i++;
		if (t->history[i])
			write(1, "\n", 1);
	}
}
