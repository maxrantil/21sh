/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/19 12:46:09 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*save_begin(t_node *n, size_t i)
{
	char	*begin_arg;
	size_t	len;

	len = ft_strclen(n->arg[i], '$');
	if (len)
	{
		begin_arg = ft_strsub(n->arg[i], 0, len);
		return (begin_arg);
	}
	return (NULL);
}

static void	change_new_arg(t_shell *sh, char **new_arg, ssize_t i)
{
	char	*temp;

	temp = ft_strdup(ft_strchr(sh->env[i], '=') + 1);
	*new_arg = ft_strupdate(*new_arg, temp);
	ft_strdel(&temp);
}

static char	*check_for_end(char **dollars)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dollars[i][j] && (ft_isalnum(dollars[i][j]) || dollars[i][j] == '_'))
		j++;
	if (dollars[i][j])
	{
		str = ft_strdup(&dollars[i][j]);
		dollars[i][j] = '\0';
		return (str);
	}
	else
		return (NULL);
}

static char	*get_new_arg(t_shell *sh, char **dollars)
{
	char	*key;
	char	*new_arg;
	char	*end_arg;
	ssize_t	i;
	ssize_t	j;

	new_arg = ft_strnew(0);
	j = -1;
	while (dollars[++j])
	{
		end_arg = check_for_end(&dollars[j]);
		key = ft_strjoin(dollars[j], "=");
		i = -1;
		while (sh->env[++i])
		{
			if (!ft_strncmp(sh->env[i], key, ft_strlen(key)))
				change_new_arg(sh, &new_arg, i);
		}
		if (end_arg)
			new_arg = ft_strupdate(new_arg, end_arg);
		ft_strdel(&end_arg);
		ft_strdel(&key);
	}
	return (new_arg);
}

void	expansions_dollar(t_node *n, t_shell *sh, char *dollar, size_t i)
{
	char	**dollars;
	char	*new_arg;
	char	*begin_arg;

	begin_arg = save_begin(n, i);
	dollars = ft_strsplit(dollar, '$');
	new_arg = get_new_arg(sh, dollars);
	ft_arrfree((void ***)&dollars, ft_arrlen((void **)dollars));
	ft_strdel(&n->arg[i]);
	if (begin_arg && new_arg)
		n->arg[i] = ft_strupdate(begin_arg, new_arg);
	else
		n->arg[i] = ft_strdup(new_arg);
	ft_strdel(&new_arg);
}
