/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:27:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 13:52:12 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_bad_fd(int file_fd, char *filename)
{
	struct stat	buf;
	int			ret;

	ret = fstat(file_fd, &buf);
	if (ret == -1)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Bad file desctiptor\n", 2);
	}
	return (ret);
}

static int	check_ambiguous_redirect(int fd, char *target, char *oper)
{
	if (fd != 1 && !check_filename_fd(target) && ft_strequ(">&-", oper) != 1)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (-1);
	}
	return (0);
}

int	check_operator_errors(int old, int file_fd, char *filename, char *oper)
{
	if ((!filename) && (!ft_strequ(oper, ">&-")))
		return(syntax_error_msg(-1));
	if (check_ambiguous_redirect(old, filename, oper) == -1)
		return (-1);
	if (check_bad_fd(file_fd, filename) == -1)
		return (-1);
	return (0);
}
