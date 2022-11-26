/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:27:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/26 16:18:49 by rvuorenl         ###   ########.fr       */
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
		exit(5);
	}
}

static void	check_ambiguous_redirect(int fd, char *target)
{
	if (fd != 1 && !check_filename_fd(target))
	{
		ft_printf("21: %s: ambiguous redirect\n", target);
		exit(6);
	}
}

void	syntax_error_msg(int exit_code)
{
	ft_printf("21: Syntax error!\n");
	exit(exit_code);
}

void	check_operator_errors(int file_fd, char *filename, char *operator)
{
	if ((!filename) && (!ft_strequ(operator, ">&-")))
		syntax_error_msg(10);
	check_ambiguous_redirect(file_fd, filename);
	check_bad_fd(file_fd, filename);
}
