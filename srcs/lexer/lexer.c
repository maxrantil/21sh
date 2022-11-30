/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:22:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/30 13:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*make_heredoc_input(char *str)
{
	size_t	len;
	int		i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == '<' && str[i - 1] == '<')
			{
				len = ft_strlen(&str[i]);
				ft_memmove((void *)&str[i], (void *)&str[i + 1], len);
			}
			i++;
		}
	}
	return (str);
}

static char	*ft_heredoc(t_term *t, char *str)
{
	if (t->heredoc)
	{
		int		fd;
		char	*file;
		char	*cpy;
		char	*ret;

		// file = ft_strjoin("/tmp/", t->delim);
		file = (t->delim);
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd)
		{
			ret = ft_strsub(str, 0, ft_strchr(str, '\n') - str);
			cpy = ft_strchr(str, '\n') + 1;
			ft_strdel(&str);
			cpy = ft_strsub(cpy, 0, ft_strrchr(cpy, '\n') - cpy);
			write(fd, cpy, ft_strlen(cpy));
			close(fd);
			return (make_heredoc_input(ret));
		}
	}
	return (str);
}

// one backslag take it away, two backslshes keep one. (last newline is always changes to \0, NOT)
char *lexer(t_term *t)
{
	int		i;
	char	*new;
	size_t	len;

	new = ft_strtrim(t->inp);
	new = ft_heredoc(t, new);
	ft_printf("RET = %s\n", new);
	if (new)
	{
		i = 0;
		while (new[i])
		{
			if (new[i] == '\\')
			{
				len = ft_strlen(&new[i]);
				ft_memmove((void *)&new[i], (void *)&new[i + 1], len);
			}
			i++;
		}
	}
	return (new);
}
