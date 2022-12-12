#include "ft_21sh.h"

void	syntax_error_msg(int exit_code)
{
	ft_putstr_fd("21sh: Syntax error!\n", 2);
	exit(exit_code); //we dont want to exit here
}
