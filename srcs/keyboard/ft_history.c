/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 16:11:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_history(t_term *t)
{
	size_t	num_incr;

	write(1, "\n", 1);
	num_incr = 0;
	while (++num_incr < t->v_history.len)
		ft_printf("%4d  %s\n", num_incr, \
		(char *)vec_get(&t->v_history, num_incr - 1));
}
