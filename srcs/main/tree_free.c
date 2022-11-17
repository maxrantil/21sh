#include "ft_21sh.h"

static void	free_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		// ft_strclr(args[i]);
		ft_strdel(&args[i]);
}

/*	recursively free tree nodes, start from root */
void	tree_free(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		tree_free(node->left);
	if (node->right)
		tree_free(node->right);
	node->left = NULL;
	node->right = NULL;
	node->type = 0;
	free_args(node->arg);
	free(node);
	node = NULL;
}
