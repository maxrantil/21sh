#include "ft_21sh.h"

void	exec_pipe_node(t_node *n, t_shell *sh/* , t_hash **ht */)
{
	int	p[2];

	if (pipe(p) < 0)
	{
		write(2, "error on pipe\n", 14);
		exit(1);
	}
	if (fork_wrap() == 0)
	{
		close(1);
		dup(p[1]);
		/* dup2(p[1], 1); */ //can we save lines like this? dup2_check2 instead ofcourse
		close(p[0]);
		close(p[1]);
		exec_tree(n->left, sh/* , ht */);
		exit(EXIT_SUCCESS);
	}
	if (fork_wrap() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		exec_tree(n->right, sh/* , ht */);
		exit(EXIT_SUCCESS);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}
