/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aggregation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:04:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/26 16:12:04 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	get_target_fd(char *filename)
{
	int	ret;

	if (check_filename_fd(filename))
		ret = ft_atoi(filename);
	else
		ret = open_check(filename, REDIROVER);
	return (ret);
}

int	get_redirected_fd(char *full)
{
	int	fd;

	fd = ft_atoi(full);
	if (fd == 0)
		return (1);
	return (fd);
}

char	*get_redirect_operator(char *full)
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

char	*get_target_file(char *full, char *filename, size_t oper_len)
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
