#include "ft_21sh.h"

static int	exec_args(t_node *node, t_msh *msh, t_builtin **ht)
{
	t_builtin	*tmp;
	size_t		index;

	index = hash_function(node->arg[0]);
	tmp = ht[index];
	while (tmp)
	{
		if (ft_strcmp(node->arg[0], tmp->program) == 0)
			return (tmp->function(node, msh));
		tmp = tmp->next;
	}
	return (exec_21sh(node, msh, ht));
}

int	exec_tree(t_node *node, t_msh *msh, t_builtin **ht)
{
	int ret;

	ret = 1;
	if (!node)
		return (0);
	if (node->type == EXEC)
		ret = exec_args(node, msh, ht);
	else if (node->type == PIPE)
		exec_pipe_node(node, msh, ht);
	else if (node->type == REDIROVER || node->type == REDIRAPP)
		redirection_file(node, msh, ht);
	else if (node->type == REDIRIN)
		input_file_read(node->arg[0]);
	else if (node->type == AMP)
	{
		if (fork_check() == 0)
		{
			// exec_tree(node->left, msh, ht);
			execve(node->arg[0], node->arg, msh->env); //this is 42sh shit, make better error handling etc
			exit(EXIT_SUCCESS);
		}
	}
	else if (node->type == SEMI)
	{
		exec_tree(node->left, msh, ht);
		exec_tree(node->right, msh, ht);
	}
	return (ret);
}
