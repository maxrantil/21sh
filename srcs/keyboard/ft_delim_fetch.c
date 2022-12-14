/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim_fetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:38:58 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 14:20:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_isseparator(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
 * It prints an error message
 * when the user enters a syntax error
 *
 * @param t the term structure
 * @param ptr the pointer to the current character in the input string
 */
static void	delim_fetch_error(t_term *t, char *ptr)
	{
	if (*ptr && ft_isseparator(*ptr))
	{
		ft_putstr_fd("\n21sh: syntax error near unexpected token `", 2);
		write(2, ptr, 1);
		ft_putstr_fd("'", 2);
	}
	else
		ft_putstr_fd("\n21sh: syntax error near unexpected token `newline'", 2);
	ft_strclr(t->inp);
	t->heredoc = 0;
}

/**
 * It returns a pointer to the
 * first character after the second '<' character in the input string
 *
 * @param t the terminal structure
 *
 * @return The pointer to the first character after the second delimiter.
 */
static char	*strdelim(t_term *t)
{
	char	*ptr;
	int		delim_qty;

	ptr = t->inp;
	delim_qty = 0;
	while (*ptr)
	{
		if (*ptr == '<')
			delim_qty++;
		if (delim_qty == 2)
			return (ptr + 1);
		ptr++;
	}
	return (ptr);
}

/*
 * It fetches the delimiter
 * for a heredoc
 *
 * @param t the term structure
 */
int	ft_delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = strdelim(t);
		while (*ptr && ft_isspace(ptr))
			ptr++;
		if (*ptr && !ft_isseparator(*ptr))
		{
			end_q = ptr;
			while (*end_q && !ft_isspace(end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, end_q - ptr);
		}
		else
		{
			delim_fetch_error(t, ptr);
			return (1);
		}
	}
	return (0);
}
