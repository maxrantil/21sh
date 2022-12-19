/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:07:22 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/19 12:33:16 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	redirection_file(t_node *n, t_shell *sh)
{
	int	file_fd;
	int	redirected_fd;

	redirected_fd = ft_atoi(n->arg[0]);
	if (redirected_fd == 0)
		redirected_fd = 1;
	file_fd = open_check(n->arg[1], n->type);
	if (file_fd != -1)
	{
		if (dup2_wrap(file_fd, redirected_fd) >= 0)
			exec_tree(n->left, sh);
		close(file_fd);
	}
}
