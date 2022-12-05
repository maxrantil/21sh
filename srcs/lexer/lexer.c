/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:22:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/05 12:56:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*change_delim_to_file(t_term *t, char *str) //cat<<EOF>file dosnt work
{
	size_t	i;
	size_t	len_needle;
	char	*pre_needle;
	char	*post_needle;
	char	*ret;

	i = 0;
	post_needle = NULL;
	len_needle = ft_strlen(t->delim);
	while (str && str[i])
	{
		if (!ft_strnequ(&str[i], t->delim, len_needle))
			i++;
		else
			break ;
	}
	if (str && str[i])
	{
		pre_needle = ft_strsub(str, 0, i);
		if (ft_strlen(str) > (i + len_needle))
		{
			post_needle = ft_strsub(str, i + len_needle, ft_strlen(str) - (i + len_needle));
			ret = ft_strjoin_three(pre_needle, "/tmp/heredoc", post_needle);
			ft_strdel(&post_needle);
		}
		else
			ret = ft_strjoin(pre_needle, "/tmp/heredoc");
		ft_strdel(&pre_needle);
		ft_strdel(&str);
		return (ret);
	}
	return (NULL);
}

static char	*make_heredoc_input(t_term *t, char *str)
{
	size_t	len;
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (i && str[i] == '<' && str[i - 1] == '<')
		{
			len = ft_strlen(&str[i]);
			ft_memmove((void *)&str[i], (void *)&str[i + 1], len);
		}
		i++;
	}
	return (change_delim_to_file(t, str));
}

static char	*ft_heredoc(t_term *t, char *str)
{
	if (t->heredoc)
	{
		int		fd;
		char	*file;
		char	*cpy;
		char	*ret;

		file = "/tmp/heredoc";
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd)
		{
			ret = ft_strsub(str, 0, ft_strchr(str, '\n') - str);
			cpy = ft_strchr(str, '\n') + 1;
			if (ft_strrchr(cpy, '\n'))
				cpy = ft_strsub(cpy, 0, ft_strrchr(cpy, '\n') - cpy);
			if (!ft_strequ(cpy, t->delim))
			{
				write(fd, cpy, ft_strlen(cpy));
				ft_strdel(&cpy);
			}
			else
				write(fd, "\0", 1);
			ft_strdel(&str);
			close(fd);
			return (make_heredoc_input(t, ret));
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
	i = 0;
	while (new && new[i])
	{
		if (new[i] == '\\')
		{
			len = ft_strlen(&new[i]);
			ft_memmove((void *)&new[i], (void *)&new[i + 1], len);
		}
		i++;
	}
	return (new);
}
