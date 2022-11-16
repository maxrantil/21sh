#include "ft_21sh.h"

static int	exec_args(t_node *node, t_msh *msh, t_builtin **ht)
{
	t_builtin	*tmp;
	size_t		index;

	index = hash_function(node->arg[0]);
	// hash_print(ht);
	// ft_printf("index: %d\n", index);
	tmp = ht[index];
	while (tmp)
	{
		if (ft_strcmp(node->arg[0], tmp->program) == 0)
			return (tmp->function(node, msh));
		tmp = tmp->next;
	}
	return (exec_21sh(node, msh));
}

int	exec_tree(t_node *node, t_msh *msh, t_builtin **ht)
{
	int ret;

	ret  = 1;
	if (!node)
		exit(1);
	if (node->type == EXEC)
	{
		if (!node->arg[0])
			exit(1);
		ret = exec_args(node, msh, ht);
	}
	else if (node->type == PIPE)
		exec_pipe_node(node, msh, ht);
	else if (node->type == REDIROVER || node->type == REDIRAPP)
		redirection_file(node, msh, ht);
	else if (node->type == REDIRIN)
		input_file_read(node->arg[0]);
	else if (node->type == AMP)
	{
		if (fork_check() == 0)
			exec_tree(node->left, msh, ht);
	}
	else if (node->type == SEMI)
	{
		if (fork_check() == 0)
			exec_tree(node->left, msh, ht);
		wait(0);
		exec_tree(node->right, msh, ht);
	}
	// exit(0);
	return (ret);
}
