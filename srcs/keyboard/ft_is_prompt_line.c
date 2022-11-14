/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prompt_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/14 13:06:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

char	*ft_is_prompt_line(t_term *t, ssize_t row)
{
	if (!row || t->nl_addr[row][-1] == '\n')
		return (t->nl_addr[row]);
	return (NULL);
}
