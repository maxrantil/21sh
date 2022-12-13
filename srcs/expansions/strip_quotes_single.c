/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes_single.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:02:44 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 15:02:57 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

size_t	strip_quotes_single(char *str, size_t quote1)
{
	size_t	len;
	ssize_t	quote2;

	len = ft_strlen(str);
	quote2 = find_matching_quote(&(str[quote1]), str[quote1]);
	quote2 += quote1;
	ft_memmove(&(str[quote1]), &(str[quote1 + 1]), len - quote1);
	ft_memmove(&(str[quote2 - 1]), &(str[quote2]), len - quote2);
	return (quote2 - 2);
}
