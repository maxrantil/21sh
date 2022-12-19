/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_aggregations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:24:12 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/19 14:06:18 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	convert_operator(char **operator)
{
	free(*operator);
	*operator = ft_strdup(">&-");
}

static char	*get_target_file(char *full, char *filename, size_t oper_len)
{
	size_t	target_len;
	size_t	i;

	i = 0;
	while (full[i] != '>' && full[i] != '<' && full[i] != '&' && full[i])
		i++;
	target_len = ft_strlen(full) - oper_len - i;
	if (target_len == 0)
	{
		if (filename)
			return (ft_strdup(filename));
		syntax_error_msg(-1);
	}
	else
		return (ft_strsub(full, i + oper_len, target_len));
	return (NULL);
}

static char	*get_redirect_operator(char *full)
{
	int	i;
	int	len;

	i = 0;
	while (full[i])
	{
		while (full[i] != '>' && full[i] != '<' && full[i] != '&' && full[i])
			i++;
		len = i;
		while (full[len] == '>' || full[len] == '<' || full[len] == '&'
			|| full[len] == '-')
			len++;
		len -= i;
		return (ft_strsub(full, i, (size_t)len));
	}
	return (ft_strdup(""));
}

static int	get_redirected_fd(char *full, char *oper, char *targ)
{
	int	fd;

	fd = ft_atoi(full);
	if (fd == 0 && (ft_strequ(">&", oper) == 1) && (ft_strequ("-", targ) == 1))
		return (1);
	return (fd);
}

void	check_file_aggregations(t_node *n, t_shell *sh)
{
	int		file_fd;
	char	*operator;
	char	*target_file;
	int		ret;

	operator = get_redirect_operator(n->arg[0]);
	target_file = get_target_file(n->arg[0], n->arg[1], ft_strlen(operator));
	file_fd = get_redirected_fd(n->arg[0], operator, target_file);
	if ((ft_strequ("-", target_file) == 1)
		&& ((ft_strequ(">&", operator) == 1)
			|| (ft_strequ("<&", operator) == 1)))
		convert_operator(&operator);
	ret = 0;
	if ((ft_strequ((const char *)operator, "&>") == 1)
		|| (ft_strequ((const char *)operator, ">&") == 1)
		|| (ft_strequ((const char *)operator, "<&") == 1))
		ret = redirect_aggregate(file_fd, target_file, operator);
	else if (ft_strequ((const char *)operator, ">&-"))
		close(file_fd);
	else
		ret = syntax_error_msg(-1);
	ft_strdel(&operator);
	ft_strdel(&target_file);
	if (ret != -1)
		exec_tree(n->left, sh);
}
