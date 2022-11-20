#include "ft_21sh.h"

static int	open_check(char *filename, int mode)
{
	int	file_fd;

	file_fd = -1;
	if (mode == REDIROVER) // >
		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == REDIRAPP) // >>
		file_fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		write(2, "error on open_mode\n", 19);
		exit(10);
	}
	return (file_fd);
}

void	redirection_file(t_node *n, t_shell *sh, t_hash **ht)
{
	int file_fd;

	file_fd = open_check(n->arg[0], n->type);	//	1 == > , 2 == >>
	if (fork_wrap() == 0)
	{
		dup2_check(file_fd);
		exec_tree(n->left, sh, ht);
		exit(11);
	}
	wait(0);
	close(file_fd);
}
