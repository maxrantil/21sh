#include "ft_21sh.h"

static void	exec_semicolon(t_node *n, t_shell *sh)
{
	reset_fds(sh->terminal_name);
	exec_tree(n->left, sh);
	reset_fds(sh->terminal_name);
	exec_tree(n->right, sh);
}

static void	exec_ampersand(t_node *n, t_shell *sh)
{
	if (fork_wrap() == 0)
	{
		// exec_tree(n->left, sh, ht);
		execve(n->arg[0], n->arg, sh->env); //this is 42sh shit, make better error handling etc
		exit(EXIT_SUCCESS);
	}
}

static size_t	num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

static int	exec_args(t_node *n, t_shell *sh)
{
	size_t	i;

	loop_conversions_quotes(n, sh);
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
	if (n->type == EXEC && n->arg)
		return (exec_args(n, sh));
	else if (n->type == PIPE)
		exec_pipe_node(n, sh);
	else if (n->type == REDIROVER || n->type == REDIRAPP)
		redirection_file(n, sh);
	else if (n->type == REDIRIN)
		input_file_read(n->arg[1]);
	else if (n->type == FILEAGG)
		check_file_aggregations(n, sh);
	else if (n->type == AMP)
		exec_ampersand(n, sh);
	else if (n->type == SEMI)
		exec_semicolon(n, sh);
	return (1);
}
