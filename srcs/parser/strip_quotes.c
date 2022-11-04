/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_strip_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:18:22 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/31 10:34:16 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	strip_quotes(char **args)
{
	ssize_t	i;
	size_t	quote1;
	size_t	quote2;
	size_t	len;

	while (*args)
	{
		i = -1;
		len = ft_strlen(*args);
		while ((*args)[++i])
		{
			if ((*args)[i] == '\'' || (*args)[i] == '"')
			{
				quote1 = (size_t)i;
				quote2 = find_matching_quote(&(*args)[i], (*args)[i]);
				quote2 += quote1;
				ft_memmove((void *)&(*args)[i], \
				(void *)&(*args)[i + 1], len - quote1);
				ft_memmove((void *)&(*args)[quote2 - 1], \
				(void *)&(*args)[quote2], len - quote2);
				i = (ssize_t)quote2 - 2;
			}
		}
		args++;
	}
}