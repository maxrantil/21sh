/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_convert_rm_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:22:38 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/07 14:57:06 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static ssize_t	find_matching_quote(char *str, char quote)
// {
// 	ssize_t	i;

// 	i = 1;
// 	while (str[i] && str[i] != quote)
// 		i++;
// 	return (i);
// }

static ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	// while (str[i] && str[i] != quote)
	// 	i++;
	// return (i);

	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '\'' || str[i + 1] == '\"')
			i++;
		else if (str[i] == quote)
			break ;
		i++;
	}
	return (i);
}

size_t	strip_quotes_single(char **str, size_t quote1)
{
	// ssize_t	j;
	size_t	len;
	ssize_t	quote2;

	len = 0;
	// j = quote1;
	len = ft_strlen(*str);
	quote2 = find_matching_quote(&(*str[quote1], *str[quote1]));
	quote2 += quote1;
	ft_memmove(&(*str[quote1]), &(*str[quote1 + 1]),
		len - quote1);
	ft_memmove(&(*str[quote2 - 1]), &(*str[quote2]),
		len - quote2);
	return (quote2 - 2);

	// while (*str[++j])
	// {
	// 	if (*str[j] == '\\' && *str[j + 1] == '\'')
	// 		j++;
	// 	else if (*str[j] == '\'')
	// 	{
	// 		quote2 = j + quote1;
	// 		ft_memmove(&(*str[quote1]), &(*str[quote1 + 1]),
	// 			len - quote1);
	// 		ft_memmove(&(*str[quote2 - 1]), &(*str[quote2]),
	// 			len - quote2);
	// 		return (quote2 - 2);
	// 	}
	// }
	// return (0);
}

void	convert_dollar(t_shell *sh, size_t *q2, size_t *len, char **str)
{

}

size_t	strip_quotes_double(char **str, size_t quote1, t_shell *sh)
{
	size_t	i;
	size_t	quote2;

	i = quote1;
	quote2 = find_matching_quote(&(*str[quote1], *str[quote1]));
	while (i < quote2)
	{
		if (*str[i] == '$')
		{
		}
	}
	ft_memmove(&(*str[quote1]), &(*str[quote1 + 1]),
		len - quote1);
	ft_memmove(&(*str[quote2 - 1]), &(*str[quote2]),
		len - quote2);
	return (quote2 - 2);
}

void	convert_tilde_single_quote(t_node *n, t_shell *sh)
{
	size_t	word;
	size_t	i;

	word = -1;
	while (n->arg[++word] != NULL)
	{
		i = -1;
		while (n->arg[word][++i])
		{
			if (n->arg[word][0] == '~' && (n->arg[word][1] == '/'
				|| n->arg[word][1] == '\0'))
			{
				expansions_tilde(n, sh, word);
			}
			if (n->arg[word][i] == '\\' && (n->arg[word][i + 1] == '\''
					|| n->arg[word][i + 1] == '\"')
				i++;
			else if (n->arg[word][i] == '\'')
			{
				i += strip_quotes_single(&(n->arg[word]), i);
			}
			else if (n->arg[word][i] == '\"')
			{
				i += strip_quotes_double(&(n->arg[word], i, sh);
			}
		}
	}
}

void	convert_expand_arguments(t_node *n, t_shell *sh)
{
	convert_tilde_single_quote(n, sh);
	// convert_dollar_double_quote(n, sh);
}

// static ssize_t	find_matching_quote(char *str, char quote)
// {
// 	ssize_t	i;

// 	i = 1;
// 	while (str[i])
// 	{
// 		if (str[i] == '\\' && str[i + 1] == quote)
// 			i++;
// 		else if (str[i] == quote)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }
