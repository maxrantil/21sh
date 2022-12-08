/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_convert_rm_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:22:38 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/08 19:38:39 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*get_full_env_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ((ft_isalnum(var[i])) || var[i] == '_'))
		i++;
	return (ft_strsub((const char *)var, 0, (size_t)i));
}

char	*get_post_dollar_content(char *str, int i, size_t len, size_t post_len)
{
	char	*tmp;

	tmp = ft_strsub((const char *)&str[(size_t)i + len + 1], 0, post_len);
	if (!tmp)
	{
		ft_putstr_fd("error in post_dollar. exit(12)\n", 2);
		exit(12);
	}
	return (tmp);
}

void	replace_dollar(char **str, char *cont, char **pre, char **post)
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

void	getenv_check(char **content, char *env_name)
{
	char	*tmp;

	tmp = getenv(env_name);
	// printf("\t\t(%s)\n", tmp);
	if (tmp)
		*content = ft_strdup(tmp);
	else
		*content = ft_strdup("");
	// printf("\t\t(%s)\n", *content);
}

void	update_second_quote(size_t *len, size_t *q2, size_t cont, size_t var)
{
	*len += cont - var - 1;
	if (q2 && (*q2) != 0)
		*q2 += cont - var - 1;
}

// void	ft_strclr2(char *s)
// {
// 	int	i;

// 	if (s == NULL)
// 		return ;
// 	i = 0;
// 	while (s[i])
// 	{
// 		s[i] = '\0';
// 		i++;
// 	}
// }

// void	ft_strdel2(char **as)
// {
// 	if (as == NULL)
// 		return ;
// 	ft_strclr2(*as);
// 	free(*as);
// 	*as = NULL;
// }


size_t	move_counter_content_len(char **content)
{
	size_t	cont_len;

	cont_len = ft_strlen(*content);
	// printf("j\n");

	ft_strdel(content);
	// ft_strdel2(content);

	// printf("k\n");
	return (cont_len);
}

// i pos of $, str = str
size_t	update_arg_dollar(int i, char **str, size_t *len, size_t *q2)
{
	char	*tmp;
	char	*content;
	char	*pre_dollar;
	size_t	post_len;
	size_t	env_len;

	// printf("\nDOLLAR\n");
	// printf("\nDOLLAR\n");
	// printf("\nDOLLAR\n");
	// printf("(%s), ", (*str));
	// printf("len (%zu), ", *len);
	// printf("q2 (%zu)\n", *q2);
	printf("a\n");
	pre_dollar = NULL;
	tmp = get_full_env_name(&(*str)[i + 1]);
	printf("b\n");
	env_len = ft_strlen(tmp);
	getenv_check(&content, tmp);
	printf("c\n");
	update_second_quote(len, q2, ft_strlen(content), ft_strlen(tmp));
	post_len = ft_strlen(*str) - env_len - (size_t)i - 1;
	printf("d\n");
	ft_strdel(&tmp);
	if (post_len > 0)
		tmp = get_post_dollar_content(*str, i, env_len, post_len);
	printf("e\n");
	if (i > 0)
		pre_dollar = ft_strsub((const char *)(*str), 0, (size_t)i);
	ft_strdel(str);
	printf("f\n");
	*str = ft_strnew((size_t)i + ft_strlen(content) + post_len);
	printf("g\n");
	if (!*str)
	{
		ft_putstr_fd("error in strnew update dollar. exit(9)\n", 2);
		exit(9);
	}
	printf("h\n");
	replace_dollar(str, content, &pre_dollar, &tmp);
	printf("i\n");
	return (move_counter_content_len(&content));
}

static ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;

	// while (str[i] && str[i] != quote)
	// 	i++;
	// return (i);

	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (str[i] == quote)
			break ;
		i++;
	}
	// printf("in matching ret i = (%zu)\n", i);
	return (i);
}

size_t	strip_quotes_single(char *str, size_t quote1)
{
	size_t	len;
	ssize_t	quote2;

	len = ft_strlen(str);
	quote2 = find_matching_quote(&(str[quote1]), str[quote1]);
	quote2 += quote1;
	ft_memmove(&(str[quote1]), &(str[quote1 + 1]), len - quote1);
	ft_memmove(&(str[quote2 - 1]), &(str[quote2]), len - quote2);
	return (quote2 - 2);
}

size_t	strip_quotes_double(char **str, size_t quote1)
{
	size_t	i;
	size_t	quote2;
	size_t	len;

	i = quote1;
	len = ft_strlen(*str);
	// printf("debug (%s)\n", *str);
	quote2 = find_matching_quote(&((*str)[quote1]), (*str)[quote1]);
	quote2 += quote1;
	// printf("len (%zu), q1 (%zu), q2 (%zu), i (%zu)\n", len, quote1, quote2, i);
	while (i < quote2)
	{
		// printf("inside i (%zu) q2 (%zu)\n", i, quote2);
		// printf("char (%c)\n", *str[i + 1]);
		// i++;
		if ((*str)[i] == '$')
		{
			// printf("\tinside IF\n");
			i += update_arg_dollar(i, str, &len, &quote2);
		}
		else
		{
			// printf("\tinside ELSE\n");
			i++;
		}
	}
	// printf("a\n");
	ft_memmove(&((*str)[quote1]), &((*str)[quote1 + 1]), len - quote1);
	// printf("b\n");
	ft_memmove(&((*str)[quote2 - 1]), &((*str)[quote2]), len - quote2);
	// printf("c\n");
	return (quote2 - 2);
}

void	loop_conversions_quotes(t_node *n, t_shell *sh)
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
					|| n->arg[word][i + 1] == '\"'))
				i++;
			else if (n->arg[word][i] == '\'')
			{
				// starting i = first quote
				i += strip_quotes_single(n->arg[word], i);
				// last should be letter before last quote
			}
			else if (n->arg[word][i] == '\"')
			{
				// printf("i (%zu) - ", i);
				i = strip_quotes_double(&(n->arg[word]), i);
				// printf("i (%zu)\n", i);
			}
			else if (n->arg[word][i] == '$')
			{
				size_t	word_len;
				word_len = ft_strlen(n->arg[word]);
				i = update_arg_dollar(i, &(n->arg[word]), &word_len, 0);
				// printf("after dollar (%zu) str(%s)\n", i, n->arg[word]);
				i--;
			}
		}
	}
}

/*
0123456
'hello'

q1 = 0
q2 = 6
len = 7

0123456
hello
*/

/*

012345678901
"$USER.t"
q2 = 8
var_len = 4+1
012345678901	1 -> 9
"rvuorenl.t"
q2 = 11
cont_len = 8

0123456789012
"$USERNAME.t"
q2 = 12
var_len = 8+1
012345678901	1 -> 3
"rv.t"
q2 = 11
cont_len = 2

*/
