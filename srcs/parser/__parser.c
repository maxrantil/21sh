/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:47:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static size_t	count_quotes(char *p)
{
	size_t	found;
	int		quote;

	found = 1;
	while (*p)
	{
		if (*p == '\'' || *p == '"')
		{
			found = 0;
			quote = *p++;
			while (*p && *p != quote)
				p++;
			if (*p == quote)
				found = 1;
		}
		p++;
	}
	return (found);
}

static void	trim_cl(char **cl)
{
	char	*trimmed;

	trimmed = ft_strtrim(*cl);
	ft_strdel(cl);
	*cl = trimmed;
}

int	parser(t_msh *msh)
{
	trim_cl(&msh->cl);
	if (*msh->cl)
	{
		if (!count_quotes(msh->cl))
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (-1);
		}
		msh->args = get_arguments(msh->cl, count_arguments(msh->cl));
		strip_quotes(msh->args);
		expansions(msh);
		return (1);
	}
	return (-1);
}
