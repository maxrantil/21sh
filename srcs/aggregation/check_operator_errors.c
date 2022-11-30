/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:27:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/29 15:33:25 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	check_bad_fd(int file_fd, char *filename)
{
	struct stat	buf;
	int			ret;

	ret = fstat(file_fd, &buf);
	if (ret == -1)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Bad file desctiptor\n", 2);
		exit(5);
	}
}

static void	check_ambiguous_redirect(int fd, char *target, char *oper)
{
	if (fd != 1 && !check_filename_fd(target) && ft_strequ(">&-", oper) != 1)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		exit(6);
	}
}

void	check_operator_errors(int old, int file_fd, char *filename, char *oper)
{
	if ((!filename) && (!ft_strequ(oper, ">&-")))
		syntax_error_msg(10);
	check_ambiguous_redirect(old, filename, oper);
	check_bad_fd(file_fd, filename);
}
