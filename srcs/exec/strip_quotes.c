/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:18:22 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/02 18:59:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void	strip_quotes(char **args)
{
	ssize_t	i;
	size_t	len;
	ssize_t	quote1;
	ssize_t	quote2;

	len = 0;
	while (*args)
	{
		i = -1;
		len = ft_strlen(*args);
		while ((*args)[++i])
		{
			if ((*args)[i] == '\'' || (*args)[i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&(*args)[i], (*args)[i]);
				quote2 += quote1;
				ft_memmove((void *)&(*args)[i], \
				(void *)&(*args)[i + 1], len - (size_t)quote1);
				ft_memmove((void *)&(*args)[quote2 - 1], \
				(void *)&(*args)[quote2], len - (size_t)quote2);
				i = quote2 - 2;
			}
		}
		if (*args)
			args++;
	}
}
