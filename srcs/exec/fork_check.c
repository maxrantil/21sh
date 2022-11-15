#include "ft_21sh.h"

int	fork_check(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "error on fork\n", 14);
		exit(1);
	}
	return (pid);
}
