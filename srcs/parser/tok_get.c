/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:50:09 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 11:50:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	tok_loop(char **scan, int ret)
{
	while (**scan)
	{
		if (ft_strchr("<|&;", **scan) && (*scan)++)
			break ;
		else if (**scan == '>' && (*scan)++)
		{
			if (**scan == '>' && (*scan)++)
				ret = '#';
			break ;
		}
		else
		{
			ret = 'a';
			while ((**scan && !ft_isspace(*scan) && !ft_strchr("<|&;>", **scan)) \
				|| (**scan && *(*scan + 1) \
				&& *(*scan - 1) == '\\' && **scan == '\n'))
				(*scan)++;
			break ;
		}
	}
	return (ret);
}

int	tok_get(char **ptr_to_line, char **tok, char **end_q)
{
	char	*scan;
	int		ret;

	scan = *ptr_to_line;
	scan = ft_skip_whitespaces(scan);
	if (*scan == '\0')
		return (0);
	if (tok)
		*tok = scan;
	ret = *scan;
	ret = tok_loop(&scan, ret);
	if (end_q)
		*end_q = scan;
	scan = ft_skip_whitespaces(scan);
	*ptr_to_line = scan;
	return (ret);
}
