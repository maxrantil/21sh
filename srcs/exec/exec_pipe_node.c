/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:48:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 12:12:18 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	close_pipe(int p1, int p2)
{
	close(p1);
	close(p2);
}

void	exec_pipe_node(t_node *n, t_shell *sh)
{
	int	p[2];

	if (pipe(p) < 0)
		exit(1);
	if (fork_wrap() == 0)
	{
		close(1);
		dup(p[1]);
		close_pipe(p[0], p[1]);
		exec_tree(n->left, sh);
		exit(EXIT_SUCCESS);
	}
	if (fork_wrap() == 0)
	{
		close(0);
		dup(p[0]);
		close_pipe(p[0], p[1]);
		exec_tree(n->right, sh);
		exit(EXIT_SUCCESS);
	}
	close_pipe(p[0], p[1]);
	wait(0);
	wait(0);
}
