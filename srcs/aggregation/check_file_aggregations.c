/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_aggregations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:24:12 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/29 10:04:26 by mrantil          ###   ########.fr       */
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
	while (full[i] != '>' && full[i] != '|' && full[i] != '&' && full[i])
		i++;
	target_len = ft_strlen(full) - oper_len - i;
	if (target_len == 0)
	{
		if (filename)
			return (ft_strdup(filename));
		syntax_error_msg(9);
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
		while (full[i] != '>' && full[i] != '|' && full[i] != '&' && full[i])
			i++;
		len = i;
		while (full[len] == '>' || full[len] == '|' || full[len] == '&'
			|| full[len] == '-')
			len++;
		len -= i;
		return (ft_strsub(full, i, (size_t)len));
	}
	return (ft_strdup(""));
}

static int	get_redirected_fd(char *full)
{
	int	fd;

	fd = ft_atoi(full);
	if (fd == 0)
		return (1);
	return (fd);
}

void	check_file_aggregations(char *full, char *filename)
{
	int		file_fd;
	char	*operator;
	char	*target_file;

	file_fd = get_redirected_fd(full);
	operator = get_redirect_operator(full);
	target_file = get_target_file(full, filename, ft_strlen(operator));
	if ((ft_strequ("-", target_file) == 1) && (ft_strequ(">&", operator) == 1))
		convert_operator(&operator);
	if ((ft_strequ((const char *)operator, "&>"))
		|| (ft_strequ((const char *)operator, ">&")))
	{
		redirect_aggregate(file_fd, target_file, operator);
	}
	else if (ft_strequ((const char *)operator, ">&-"))
		close(file_fd);
	else
		syntax_error_msg(1);
	ft_strdel(&operator);
	ft_strdel(&target_file);
}
