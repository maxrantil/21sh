/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matching_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:18:23 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 15:06:46 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'
				|| str[i + 1] == '\\' ))
			i++;
		else if (str[i] == quote)
			break ;
		i++;
	}
	return (i);
}
