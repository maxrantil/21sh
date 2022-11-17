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
	if (root->type == EXEC)
	{
		size_t len = ft_arrlen((void **)root->arg);
		if (len > 2)
			printf("%s %s ...\n", root->arg[0], root->arg[1]);
		else if (len == 2)
			printf("%s %s\n", root->arg[0], root->arg[1]);
		else
			printf("%s\n", root->arg[0]);
	}
	else if (root->type == PIPE)
		printf("|");
	else if (root->type == REDIROVER)
			printf("> %s\n", root->arg[0]);
	else if (root->type == REDIRAPP)
		printf(">> %s\n", root->arg[0]);
	else if (root->type == REDIRIN)
		printf("< %s\n", root->arg[0]);
	else if (root->type == AMP)
		printf("&");
	else if (root->type == SEMI)
		printf(";");
	rec_print_tree(root->left, lvl);
}

void	tree_print(t_node *root)
{
	write(1, "\n-------------------------- TREE PRINT --------------------------\n", 66);
	rec_print_tree(root, 0);
	write(1, "\n-------------------------- TREE PRINT --------------------------\n\n", 67);
}
