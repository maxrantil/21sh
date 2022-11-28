/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_aggregations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:24:12 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/28 21:25:56 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	convert_operator(char **operator)
{
	free(*operator);
	*operator = ft_strdup(">&-");
}

static void	redirect_aggregate(int old_fd, char *target, char *operator)
{
	int	new_fd;

	new_fd = get_target_fd(target);
	check_operator_errors(old_fd, new_fd, target, operator);
	if (old_fd == 1 || old_fd == 2)
	{
		if (new_fd != 1)
			dup2_check2(new_fd, 1);
		if (new_fd != 2)
			dup2_check2(1, 2);
	}
	else
		dup2_check2(new_fd, old_fd);
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
