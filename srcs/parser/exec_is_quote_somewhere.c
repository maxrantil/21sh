/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_quote_somewhere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:02:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 12:12:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	loop_tok(char **tok, int len)
{
	int	quote;

	quote = **tok;
	++(*tok);
	while (**tok && **tok != quote && ++len)
		(*tok)++;
	while (**tok && !ft_isspace((const char *)*tok) && ++len)
		(*tok)++;
	return (len);
}

int	exec_is_quote_somewhere(char *tok)
{
	int	len;

	len = 0;
	while (*tok && !ft_isspace((const char *)tok) && ++len)
	{
		if (*tok == '\'' || *tok == '"')
		{
			if (tok[1] && *(tok - 1) == '\\')
				if (tok[2] && *(tok - 2) != '\\' && tok++)
					continue ;
			len = loop_tok(&tok, len);
			if (*tok == '\'' || *tok == '"')
				if (tok[1] && *(tok - 1) == '\\')
					if (tok[2] && *(tok - 2) != '\\')
						continue ;
			return (len);
		}
		tok++;
	}
	return (0);
}
