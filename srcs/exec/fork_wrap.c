#include "ft_21sh.h"

pid_t	fork_wrap(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("error on fork", 2);
		exit(1);
	}
	return (pid);
}
