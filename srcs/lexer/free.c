#include "temp.h"
void	ft_free_doublearray(char ***array);
void	ft_strdel(char **as);

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
	ft_free_doublearray(&(node->arg));
	ft_strdel(node->command);
	free(*node);
	node = NULL;
}

// typedef struct s_node
// {
// 	int				type;
// 	char			*arg[100];
// 	struct s_node	*command;
// 	struct s_node	*left;
// 	struct s_node	*right;
// }				t_node;

void	ft_strdel(char **as)
{
	if (as == NULL)
		return ;
	ft_strclr(*as);
	free(*as);
	*as = NULL;
}

void	ft_free_doublearray(char ***array)
{
	int	i;

	i = -1;
	if (*array)
	{
		while ((*array)[++i])
			ft_strdel(&(*array)[i]);
		free((*array)[i]);
		free(*array);
		*array = NULL;
	}
}
