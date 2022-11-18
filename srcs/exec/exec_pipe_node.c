#include "ft_21sh.h"

void	exec_pipe_node(t_node *node, t_msh *msh, t_builtin **ht)
{
	int	p[2];

	if (pipe(p) < 0)
	{
		write(2, "error on pipe\n", 14);
		exit(1);
	}
	if (fork_check() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		exec_tree(node->left, msh, ht);
		exit(0);
	}
	if (fork_check() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		exec_tree(node->right, msh, ht);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}
