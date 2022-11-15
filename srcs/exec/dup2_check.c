#include "ft_21sh.h"

int	dup2_check(int file_fd)
{
	int	dup2_fd;

	dup2_fd = dup2(file_fd, 1);
	if (dup2_fd == -1)
	{
		write(2, "error on dup2_check\n", 20);
		exit(11);
	}
	return (dup2_fd);
}
