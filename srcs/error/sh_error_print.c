/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:45:05 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 17:43:43 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	print_status(int status, char *arg)
{
	struct stat	statbuf;

	if (status == -1)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	if (status == -2)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	if (status == 0)
	{
		lstat(arg, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Exec format error\n", STDERR_FILENO);
	}
}

static int	check_address(char *addr)
	{
	if (access(addr, F_OK) != 0)
		return (-1);
	if (access(addr, X_OK) != 0)
		return (-2);
	return (0);
}

static void	print_usage(char *arg, int status)
{
	if (ft_strequ(arg, "."))
	{
		ft_putstr_fd("21sh: .: filename argument required\n", \
		STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd("21sh: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	if (!ft_strchr(arg, '/'))
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		print_status(status, arg);
}

static void	print_setenv_error(char *arg)
{
	ft_putstr_fd("21sh: setenv: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	sh_error_print(char *arg, int i)
{
	int	status;

	status = check_address(arg);
	if (i == 1)
		ft_putstr_fd("error, invalid argument\n", STDERR_FILENO);
	else if (i == 2)
		ft_putstr_fd("usage: 'env key=value'\n", STDERR_FILENO);
	else if (i == 3)
	{
		ft_putstr_fd("error, malloc error\n", STDERR_FILENO);
		exit(1);
	}
	else if (i == 4)
		print_usage(arg, status);
	else if (i == 5)
	{
		ft_printf("21sh: cd: %s", arg);
		print_status(status, arg);
	}
	else if (i == 6)
		print_setenv_error(arg);
	else if (i == 7)
		print_status(status, arg);
}
