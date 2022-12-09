/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:07:22 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/08 14:22:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	redirection_file(t_node *n, t_shell *sh/* , t_hash **ht */)
{
	int	file_fd;
	int	redirected_fd;

	redirected_fd = ft_atoi(n->arg[0]);
	if (redirected_fd == 0)
		redirected_fd = 1;
	file_fd = open_check(n->arg[1], n->type);
	dup2_check2(file_fd, redirected_fd);
	exec_tree(n->left, sh/* , ht */);
	close(file_fd);
}
