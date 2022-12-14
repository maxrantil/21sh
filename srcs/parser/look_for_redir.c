/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:12:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/19 14:32:02 by rvuorenl         ###   ########.fr       */
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

static int	get_fd_after(char *tok)
{
	if (!*tok || (*tok == '<' || *tok == '>' \
		|| *tok == '|' || *tok == ';'))
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
		if (((*tok == '>' && *(tok + 1) == '>') \
			|| (*tok == '<' && *(tok + 1) == '<')) && ++ret)
			tok++;
		tok++;
		while (*tok && ft_isspace(tok))
			tok++;
		if (!get_fd_after(tok))
			return (-1);
		return (++ret);
	}
	else
		return (0);
}

int	check_for_fileagg(char *tok)
{
	int		ret;

	ret = 0;
	ret = loop_tok(&tok, ret);
	if ((*tok == '>' || *tok == '<') && *(tok + 1) == '&' && ++ret)
	{
		tok++;
		tok++;
		while (*tok && ft_isspace(tok))
			tok++;
		if (!get_fd_after(tok))
			return (-1);
		return (++ret);
	}
	else
		return (0);
}

void	look_for_redir(t_line *l, char **ptr_to_line)
{
	l->fileagg_len = check_for_fileagg(*ptr_to_line);
	l->fd_len = get_fd_before(*ptr_to_line);
}
