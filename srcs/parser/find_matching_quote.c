/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matching_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:47:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
