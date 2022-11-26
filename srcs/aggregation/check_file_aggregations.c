/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_aggregations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:24:12 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/26 16:05:16 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	check_file_aggregations(char *full, char *filename)
{
	int		file_fd;
	char	*operator;
	char	*target_file;
	int		target_fd;

	file_fd = get_redirected_fd(full);
	operator = get_redirect_operator(full);
	target_file = get_target_file(full, filename, ft_strlen(operator));
	check_operator_errors(file_fd, target_file, operator);
	if ((ft_strequ((const char *)operator, "&>"))
		|| (ft_strequ((const char *)operator, ">&")))
	{
		target_fd = get_target_fd(target_file);
		dup2_check2(target_fd, 1);
		dup2_check2(1, 2);
	}
	else if (ft_strequ((const char *)operator, ">&-"))
		close(file_fd);
	else
		syntax_error_msg(1);
	ft_strdel(&operator);
	ft_strdel(&target_file);
}
