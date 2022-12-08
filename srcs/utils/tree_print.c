#include "ft_21sh.h"

void	rec_print_tree(t_node *root, int lvl)
{
	if (root == NULL)
		return ;
	lvl += COUNT;
	rec_print_tree(root->right, lvl);
	printf("\n");
	for (int i = COUNT; i < lvl; i++)
		printf(" ");
	if (root->type == EXEC && root->arg)
	{
		size_t len = ft_arrlen((void **)root->arg);
		printf("exec ");
		if (len > 2)
			printf("[%s] [1]%s [2]%s [3]%s\n", root->arg[0], root->arg[1], root->arg[2], root->arg[3]);
		else if (len == 2)
			printf("[%s] %s\n", root->arg[0], root->arg[1]);
		else
			printf("[%s]\n", root->arg[0]);
	}
	else if (root->type == PIPE)							// |
		printf("[|]");
	else if (root->type == REDIROVER && root->arg)			// >
		printf("> [%s] [%s]\n", root->arg[0], root->arg[1]);
	else if (root->type == REDIRAPP && root->arg) 			// >>
		printf(">> [%s] [%s]\n", root->arg[0], root->arg[1]);
	else if (root->type == REDIRIN && root->arg)			// <
		printf("< [%s] [%s]\n", root->arg[0], root->arg[1]);
	else if (root->type == AMP)								// &
		printf("[&]");
	else if (root->type == SEMI)							// ;
		printf("[;]");
	else if (root->type == FILEAGG && root->arg)			// >&
		printf(">& [%s] [%s]\n", root->arg[0], root->arg[1]);
	rec_print_tree(root->left, lvl);
}

void	tree_print(t_node *root)
{
	write(1, "\n-------------------------- TREE PRINT --------------------------\n", 66);
	if (root)
		rec_print_tree(root, 0);
	write(1, "\n-------------------------- TREE PRINT --------------------------\n\n", 67);
}
