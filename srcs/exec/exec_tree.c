/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:40:12 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/19 12:45:19 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	exec_semicolon(t_node *n, t_shell *sh)
{
	reset_fds(sh->term_name);
	exec_tree(n->left, sh);
	reset_fds(sh->term_name);
	exec_tree(n->right, sh);
}

static size_t	num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

static int	exec_args(t_node *n, t_shell *sh)
{
	size_t	i;

	if (!n->arg || !n->arg[0])
		return (1);
	i = 0;
	while (i < num_builtins())
	{
		if (!ft_strcmp(n->arg[0], g_builtin_str[i]))
			return (g_builtin_func[i](n, sh));
		i++;
	}
	return (exec_21sh(n, sh));
}

int	exec_tree(t_node *n, t_shell *sh)
{
	if (!n)
		return (1);
	loop_conversions_quotes(n, sh);
	if (n->type == EXEC && n->arg)
		return (exec_args(n, sh));
	else if (n->type == PIPE)
		exec_pipe_node(n, sh);
	else if (n->type == REDIROVER || n->type == REDIRAPP)
		redirection_file(n, sh);
	else if (n->type == REDIRIN)
		input_file_read(n, sh);
	else if (n->type == FILEAGG)
		check_file_aggregations(n, sh);
	else if (n->type == SEMI)
		exec_semicolon(n, sh);
	return (1);
}
