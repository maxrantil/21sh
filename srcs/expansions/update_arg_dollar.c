/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_arg_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:20:08 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 15:12:02 by rvuorenl         ###   ########.fr       */
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

static void	update_quote(size_t *len, size_t *q2, size_t cont, size_t var)
{
	if (len && (*len) != 0)
		*len += cont - var - 1;
	if (q2 && (*q2) != 0)
		*q2 += cont - var - 1;
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
	if (!tmp)
	{
		ft_putstr_fd("error in post_dollar. exit(12)\n", 2);
		exit(12);
	}
	return (tmp);
}

size_t	update_arg_dollar(int i, char **str, size_t *len, size_t *q2)
{
	char	*tmp;
	char	*content;
	char	*pre_dollar;
	size_t	post_len;
	size_t	env_len;

	pre_dollar = NULL;
	fill_env(&tmp, &content, &env_len, &(*str)[i + 1]);
	update_quote(len, q2, ft_strlen(content), ft_strlen(tmp));
	post_len = ft_strlen(*str) - env_len - (size_t)i - 1;
	ft_strdel(&tmp);
	if (post_len > 0)
		tmp = get_post_dollar_content(*str, i, env_len, post_len);
	if (i > 0)
		pre_dollar = ft_strsub((const char *)(*str), 0, (size_t)i);
	ft_strdel(str);
	*str = ft_strnew((size_t)i + ft_strlen(content) + post_len);
	if (!*str)
	{
		ft_putstr_fd("error in strnew update dollar. exit(9)\n", 2);
		exit(9);
	}
	replace_dollar(str, content, &pre_dollar, &tmp);
	return (move_counter_content_len(&content));
}
