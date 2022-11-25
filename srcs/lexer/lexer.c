/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:22:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/25 14:59:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// one backslag take it away, two backslshes keep one. (last newline is always changes to \0, NOT)
char *lexer(char *str)
{
	int		i;
	char	*new;

	new = ft_strtrim(str);
	if (new)
	{
		i = 0;
		while (*str)
		{
			if (*str == '\\')
				str++;
			new[i++] = (*str++);
		}
	}
	return (new);
}
