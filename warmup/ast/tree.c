#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 10

typedef struct s_tree
{
	int			value;
	char		*op;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

//	    +
//	   / \
//	  1   *
//	     / \
//	    2   3

t_tree *create_tree(char *op, int value)
{
	t_tree *node = (t_tree *)malloc(sizeof(t_tree));
	if (node != NULL)
	{
		node->op = op;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

void	printtree_rec(t_tree *root, int lvl)
{
	if (root == NULL)
		return ;
	lvl += COUNT;
	printtree_rec(root->right, lvl);
	printf("\n");
	for (int i = COUNT; i < lvl; i++)
		printf(" ");
	if (root->op)
		printf("%s", root->op);
	else
		printf("%d", root->value);
	printtree_rec(root->left, lvl);
}

void tree_print(t_tree *root) {
	printtree_rec(root, 0);
}

static int 	count_tree(t_tree *tree)
{
	if (tree->value > 0)
		return (tree->value);
	if (!strcmp(tree->op, "+"))
	{
		return (count_tree(tree->left) + count_tree(tree->right));
	}
	else if (!strcmp(tree->op, "*"))
	{
		return (count_tree(tree->left) * count_tree(tree->right));
	}
	return 0;
}

int main()
{
	t_tree *root_tree = create_tree("+", 0);
	t_tree *mult_tree = create_tree("*", 0);
	t_tree *one_tree = create_tree(NULL, 1);
	t_tree *two_tree = create_tree(NULL, 2);
	t_tree *three_tree = create_tree(NULL, 3);
	root_tree->left = one_tree;
	root_tree->right = mult_tree;
	mult_tree->left = two_tree;
	mult_tree->right = three_tree;
	tree_print(root_tree);
	printf("\n\nResult: %d\n", count_tree(root_tree));

	free(root_tree);
	free(mult_tree);
	free(one_tree);
	free(two_tree);
	free(three_tree);
	return 0;
}

