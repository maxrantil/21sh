/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:12:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/09 15:23:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	get_fd_before(char *tok)
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
	if (*tok == '>' || *tok == '<')
	{
		if (*tok == '>' && *(tok + 1) == '>')
		{
			if (!ft_isalnum((int)*(tok + 2)) && !ft_isspace(tok + 2))
				return (-1);
			++ret;
		} // need syntax error check here for example '> >'
		// else if (!ft_isalnum((int)*(tok + 1)) || !ft_isspace(tok + 1)) //trim here for the '<' on '<file cd -'
			// return (-1);
		return (++ret);
	}
	else
		return (0);
}
