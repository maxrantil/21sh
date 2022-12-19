/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_arg_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:20:08 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/19 13:57:08 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static size_t	move_counter_content_len(char **content)
{
	size_t	cont_len;

	cont_len = ft_strlen(*content);
	ft_strdel(content);
	return (cont_len);
}

static void	replace_dollar(char **str, char *cont, char **pre, char **post)
{
	if (*pre)
	{
		*str = ft_strcpy(*str, (const char *)*pre);
		*str = ft_strcat(*str, (const char *)cont);
		ft_strdel(pre);
	}
	else
		*str = ft_strcpy(*str, (const char *)cont);
	if (*post)
	{
		*str = ft_strcat(*str, (const char *)*post);
		ft_strdel(post);
	}
}

static char	*get_post_dollar_content(char *str, int i, size_t len, size_t post)
{
	char	*tmp;

	tmp = ft_strsub((const char *)&str[(size_t)i + len + 1], 0, post);
	return (tmp);
}

static void	init_dollar_struct(t_dollar *dollar)
{
	dollar->pre = NULL;
	dollar->content = NULL;
	dollar->env_len = 0;
}

size_t	update_arg_dollar(int i, char **str, t_shell *sh)
{
	char		*tmp;
	size_t		post_len;
	t_dollar	dol;

	init_dollar_struct(&dol);
	fill_env(&tmp, &dol, &(*str)[i + 1], sh);
	post_len = ft_strlen(*str) - dol.env_len - (size_t)i - 1;
	if (post_len > 0)
		tmp = get_post_dollar_content(*str, i, dol.env_len, post_len);
	if (i > 0)
		dol.pre = ft_strsub((const char *)(*str), 0, (size_t)i);
	ft_strdel(str);
	*str = ft_strnew((size_t)i + ft_strlen(dol.content) + post_len);
	replace_dollar(str, dol.content, &(dol.pre), &tmp);
	return (move_counter_content_len(&(dol.content)));
}
