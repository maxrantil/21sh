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
void	tree_free(t_node *n)
{
	if (!n)
		return ;
	if (n->left)
		tree_free(n->left);
	if (n->right)
		tree_free(n->right);
	n->left = NULL;
	n->right = NULL;
	// n->type = 0;
	// free_args(n->arg);
	ft_arrfree((void ***)&n->arg, ft_arrlen((void **)n->arg));
	free(n);
	n = NULL;
}
