#include "ft_21sh.h"

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
	ft_arrfree((void ***)&n->arg, ft_arrlen((void **)n->arg));
	free(n);
	n = NULL;
}
