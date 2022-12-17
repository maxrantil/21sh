/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:12:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 17:38:47 by mrantil          ###   ########.fr       */
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

static void	loop_to_end(char **tok)
{
	(*tok)++;
	while (**tok && ft_isspace(*tok))
		(*tok)++;
}

static int	get_fd_after(char *tok)
{
	if (!*tok || (!ft_isalnum(*tok) && !ft_isspace(tok) \
		&& *tok != '/' && *tok != '$' && *tok != '~'))
		return (0);
	return (1);
}

int	get_fd_before(char *tok)
{
	int		ret;

	ret = 0;
	ret = loop_tok(&tok, ret);
	if (*tok == '>' || *tok == '<')
	{
		if ((*(tok + 1) == '<' || *(tok + 1) == '>') && ++ret)
			tok++;
		loop_to_end(&tok);
		if (!get_fd_after(tok))
			return (-1);
		return (++ret);
	}
	else
		return (0);
}
