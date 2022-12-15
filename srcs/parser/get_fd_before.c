/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:12:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 12:10:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	loop_tok(char **tok, int ret)
{
	while (**tok && !ft_isspace(*tok))
	{
		if (ft_isdigit(**tok) && ++ret)
			(*tok)++;
		else
			break ;
	}
	return (ret);
}

int	get_fd_before(char *tok)
{
	int		ret;

	ret = 0;
	ret = loop_tok(&tok, ret);
	if (*tok == '>' || *tok == '<')
	{
		if (*tok == '>' && *(tok + 1) == '>')
		{
			if (!ft_isalnum((int)*(tok + 2)) && !ft_isspace(tok + 2))
				return (-1);
			++ret;
		}
		else if (*tok == '>')
		{
			tok++;
			while (*tok && ft_isspace(tok))
				tok++;
			if (!ft_isalnum(*tok))
				return (-1);
		}
		return (++ret);
	}
	else
		return (0);
}
