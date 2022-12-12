/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_convert_rm_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:22:38 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/12 17:37:03 by rvuorenl         ###   ########.fr       */
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
	if (tmp)
		*content = ft_strdup(tmp);
	else
		*content = ft_strdup("");
}

void	update_second_quote(size_t *len, size_t *q2, size_t cont, size_t var)
{
	if (len && (*len) != 0)
		*len += cont - var - 1;
	if (q2 && (*q2) != 0)
		*q2 += cont - var - 1;
}

size_t	move_counter_content_len(char **content)
{
	size_t	cont_len;

	cont_len = ft_strlen(*content);
	ft_strdel(content);
	return (cont_len);
}

void	fill_env(char **tmp, char **cont, size_t *env_len, char *str)
{
	*tmp = get_full_env_name(str);
	*env_len = ft_strlen(*tmp);
	getenv_check(cont, *tmp);
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
	update_second_quote(len, q2, ft_strlen(content), ft_strlen(tmp));
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

static ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'
			|| str[i + 1] == '\\' ))
			i++;
		else if (str[i] == quote)
			break ;
		i++;
	}
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

void	remove_backslash(char *str)
{
	size_t	len;

	if (str[1] == '\\' || str[1] == '\'' || str[1] == '\"')
	{
		len = ft_strlen(str);
		ft_memmove(str, &str[1], len);
	}
	else
	{
		printf("\tRM ELSE\n");
	}
}

void	remove_backslash_update_quote(char *str, size_t *len, size_t *q2)
{
	if (str[1] == '\\' || str[1] == '\'' || str[1] == '\"')
	{
		remove_backslash(str);
		(*len)--;
		(*q2)--;
	}
}

size_t	strip_quotes_double(char **str, size_t quote1)
{
	size_t	i;
	size_t	quote2;
	size_t	len;

	// printf("\tDOUBLE full (%s)\n", *str);

	i = quote1;
	len = ft_strlen(*str);
	quote2 = find_matching_quote(&((*str)[quote1]), (*str)[quote1]);
	quote2 += quote1;
	while (i < quote2)
	{
		if ((*str)[i] == '$')
			i += update_arg_dollar(i, str, &len, &quote2);
		else if ((*str)[i] == '\\')
		{
			remove_backslash_update_quote(&(*str)[i], &len, &quote2);
			i++;
		}
		else
			i++;
	}
	ft_memmove(&((*str)[quote1]), &((*str)[quote1 + 1]), len - quote1);
	ft_memmove(&((*str)[quote2 - 1]), &((*str)[quote2]), len - quote2);

	// printf("\tDOUBLE full (%s)\n", *str);

	return (quote2 - 2);
}

void	loop_conversions_quotes(t_node *n, t_shell *sh)
{
	size_t	word;
	size_t	i;

	word = -1;
	while (n->arg[++word] != NULL)
	{
		// printf("\tdebug full (%s)\n", n->arg[word]);
		if (n->arg[word][0] == '~' && (n->arg[word][1] == '/'
			|| n->arg[word][1] == '\0'))
			expansions_tilde(n, sh, word);
		i = -1;
		while (n->arg[word][++i])
		{
			// if (n->arg[word][i] == '\\' && (n->arg[word][i + 1] == '\''
			// 		|| n->arg[word][i + 1] == '\"'))
			// 	i++;

			if (n->arg[word][i] == '\\')
			{
				// printf("\ti = (%zu) (%s)\n", i, &n->arg[word][i]);
				// printf("\tfull (%s)\n", n->arg[word]);
				remove_backslash(&n->arg[word][i]);
				// printf("\ti = (%zu) (%s)\n", i, &n->arg[word][i]);
				// printf("\tfull (%s)\n", n->arg[word]);
			}
			else if (n->arg[word][i] == '\'')
				i = strip_quotes_single(n->arg[word], i);
			else if (n->arg[word][i] == '\"')
				i = strip_quotes_double(&(n->arg[word]), i);
			else if (n->arg[word][i] == '$')
				i = update_arg_dollar(i, &(n->arg[word]), 0, 0) - 1;
		}
	}
}
