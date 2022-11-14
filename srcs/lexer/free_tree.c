#include "parser.h"

static void	free_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
}

/*	recursively free tree nodes, start from root */
void	free_tree(t_node *node)
{
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	node->left = NULL;
	node->right = NULL;
	node->type = 0;
	free_args(node->arg);
	free(node);
	node = NULL;
}
