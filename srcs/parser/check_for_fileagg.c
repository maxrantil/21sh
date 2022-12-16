/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_fileagg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:23:13 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 14:08:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	check_for_fileagg(char *tok)
{
	int		ret;

	ret = 0;
	while (*tok && !ft_isspace(tok))
	{
		if (ft_isdigit(*tok) && ++ret)
			tok++;
		else
			break ;
	}
	if (*tok == '>' && *(tok + 1) == '&')
	{
		if (!ft_isalnum(*(tok + 2)) && (*(tok + 2)) != '-' \
			&& !ft_isspace(tok + 2) && (*(tok + 2)) != '/' \
			&& (*(tok + 2)) != '$' && (*(tok + 2)) != '~')
			return (-1);
		return (ret + 2);
	}
	else
		return (0);
}
