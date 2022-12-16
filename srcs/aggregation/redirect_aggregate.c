/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_aggregate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:42:08 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 18:49:42 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_target_fd(char *filename)
{
	int	ret;

	if (check_filename_fd(filename))
		ret = ft_atoi(filename);
	else
		ret = open_check(filename, REDIROVER);
	return (ret);
}

int	redirect_aggregate(int old_fd, char *target, char *operator)
{
	int	new_fd;

	new_fd = get_target_fd(target);
	if (new_fd != -1)
	{
		if (check_operator_errors(old_fd, new_fd, target, operator) == -1)
			return (-1);
		if (old_fd == 1 || old_fd == 2)
		{
			dup2_wrap(new_fd, 1);
			return (dup2_wrap(1, 2));
		}
		else
			return (dup2_wrap(new_fd, old_fd));
	}
	return (new_fd);
}
