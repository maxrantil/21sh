#include "ft_21sh.h"

static int	open_read_check(char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		// check reason ?
		// ft_putstr_fd(filename, 2);
		write(2, "open_read fail\n", 15);
		exit(1);
	}
	return (file_fd);
}

void	input_file_read(t_node *n, t_shell *sh)
{
	int	file_fd;

	close(0);
	file_fd = open_read_check(n->arg[1]);
	exec_tree(n->left, sh);
}
