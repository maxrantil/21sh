#include "ft_21sh.h"

static int	get_target_fd(char *filename)
{
	int	ret;

	if (check_filename_fd(filename))
		ret = ft_atoi(filename);
	else
		ret = open_check(filename, REDIROVER);
	return (ret);
}

int	redirect_aggregate(int old_fd, char *target, char *operator)
{
	int	new_fd;

	new_fd = get_target_fd(target);
	check_operator_errors(old_fd, new_fd, target, operator);
	if (old_fd == 1 || old_fd == 2)
	{
		dup2_check2(new_fd, 1);
		return (dup2_check2(1, 2));
	}
	else
		return (dup2_check2(new_fd, old_fd));
}
