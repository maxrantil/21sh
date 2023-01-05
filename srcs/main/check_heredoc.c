/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:22:47 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/05 13:25:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*find_delimiter_position(t_term *t, char *str)
{
	size_t	i;
	size_t	len_needle;
	char	*delim_pos;

	i = 0;
	len_needle = ft_strlen(t->delim);
	delim_pos = NULL;
	while (str && str[i])
	{
		if (!ft_strnequ(&str[i], t->delim, len_needle))
			i++;
		else
		{
			delim_pos = &str[i];
			break ;
		}
	}
	return (delim_pos);
}

static char	*replace_delimiter_with_file(t_term *t, char *str)
{
	size_t	len_needle;
	char	*pre_needle;
	char	*post_needle;
	char	*delim_pos;
	char	*ret;

	delim_pos = find_delimiter_position(t, str);
	if (delim_pos)
	{
		len_needle = ft_strlen(t->delim);
		pre_needle = ft_strsub(str, 0, delim_pos - str);
		if (ft_strlen(str) > (delim_pos - str + len_needle))
		{
			post_needle = ft_strsub(str, delim_pos - str + len_needle, \
			ft_strlen(str) - (delim_pos - str + len_needle));
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
	return (replace_delimiter_with_file(t, str));
}

static void	write_to_doc(t_term *t, char **cpy, int fd)
{
	if (ft_strrchr(*cpy, '\n'))
		*cpy = ft_strsub(*cpy, 0, (ft_strrchr(*cpy, '\n') + 1) - *cpy);
	if (*cpy && !ft_strequ(*cpy, t->delim))
	{
		write(fd, *cpy, ft_strlen(*cpy));
		ft_strdel(cpy);
	}
	else
		write(fd, "\0", 1);
}

char	*check_heredoc(t_term *t, char *str)
{
	int		fd;
	char	*cpy;
	char	*ret;

	if (t->heredoc && t->delim)
	{
		fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd)
		{
			ret = ft_strsub(str, 0, ft_strchr(str, '\n') - str);
			cpy = ft_strchr(str, '\n') + 1;
			write_to_doc(t, &cpy, fd);
			ft_strdel(&str);
			close(fd);
			return (make_heredoc_input(t, ret));
		}
	}
	return (str);
}
