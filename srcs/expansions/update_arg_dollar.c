/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_arg_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:20:08 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 13:12:11 by rvuorenl         ###   ########.fr       */
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
	// printf("REPLACE_DOLLAR\n");
	// 	printf("\tpre (%s)\n", *pre);
	// 	printf("\tcont (%s)\n", cont);
	// 	printf("\t*post (%s)\n", *post);
	if (*pre)
	{
		*str = ft_strcpy(*str, (const char *)*pre);
		// printf("\t*str PRE (%s)\n", *str);
		*str = ft_strcat(*str, (const char *)cont);
		ft_strdel(pre);
	}
	else
	{
		*str = ft_strcpy(*str, (const char *)cont);
	}
		// printf("\t*str MID (%s)\n", *str);
	if (*post)
	{
		*str = ft_strcat(*str, (const char *)*post);
		// printf("\t*str POST (%s)\n", *str);
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
	// printf("UPDATE_ARG_DOLLAR\n");
	// printf("\tpost_len (%zu)\n", post_len);
	// printf("\tdol.env_len (%zu)\n", dol.env_len);
	// printf("\tft_strlen(*str) (%zu)\n", ft_strlen(*str));
	// printf("\ti (%d)\n", i);
	if (post_len > 0)
	{
		tmp = get_post_dollar_content(*str, i, dol.env_len, post_len);
		// printf("\ttmp with post_len > 0 (%s)\n", tmp);
	}
	if (i > 0)
	{
		dol.pre = ft_strsub((const char *)(*str), 0, (size_t)i);
		// printf("\tdol.pre with i > 0 (%s)\n", dol.pre);
	}
	ft_strdel(str);
	*str = ft_strnew((size_t)i + ft_strlen(dol.content) + post_len);
	replace_dollar(str, dol.content, &(dol.pre), &tmp);
	return (move_counter_content_len(&(dol.content)));
}
