#include "ft_21sh.h"

/* static void	free_args(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	ft_memdel((void **)arg);
} */

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
	// node->type = 0;
	// free_args(node->arg);
	ft_arrfree((void ***)&node->arg, ft_arrlen((void **)node->arg));
	free(node);
	node = NULL;
}
