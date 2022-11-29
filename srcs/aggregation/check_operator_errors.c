/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:27:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/29 09:59:43 by mrantil          ###   ########.fr       */
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
		ft_printf("21: %s: Bad file desctiptor\n", filename);
		// exit(5);
	}
}

static void	check_ambiguous_redirect(int fd, char *target, char *oper)
{
	if (fd != 1 && !check_filename_fd(target) && ft_strequ(">&-", oper) != 1)
	{
		ft_printf("21: %s: ambiguous redirect\n", target);
		// exit(6);
	}
}

void	check_operator_errors(int old, int file_fd, char *filename, char *oper)
{
	if ((!filename) && (!ft_strequ(oper, ">&-")))
		syntax_error_msg(10);
	check_ambiguous_redirect(old, filename, oper);
	check_bad_fd(file_fd, filename);
}
