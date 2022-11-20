#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 10

typedef struct treenode {
	int value;
	struct treenode *left;
	struct treenode *right;
} treenode;

treenode *createnode(int value)
{
	treenode *n = malloc(sizeof(treenode));
	if (n != NULL)
	{
		n->value = value;
		n->left = NULL;
		n->right = NULL;
	}
	return n;
}

void printtabs(int n)
{
	for (int i = 0; i < n; i++) {
		printf("\t");
	}
}

void	printtree_rec(treenode *root, int lvl)
{
	if (root == NULL)
		return ;
	lvl += COUNT;
	printtree_rec(root->right, lvl);
	printf("\n");
	for (int i = COUNT; i < lvl; i++)
		printf(" ");
	printf("%d\n", root->value);
	printtree_rec(root->left, lvl);
}

void printtree(treenode *root) {
	printtree_rec(root, 0);
}

bool insert_tree(treenode **root, int value)
{
	treenode *n = *root;
	if (n == NULL)
	{
		*root = createnode(value);
		return true;
	}
	if (value < n->value)
	{
		if (n->left == NULL)
		{
			n->left = createnode(value);
			return true;
		}
		return insert_tree(&n->left, value);
	}
	if (value > n->value)
	{
		if (n->right == NULL)
		{
			n->right = createnode(value);
			return true;
		}
		return insert_tree(&n->right, value);
	}
	return false;
}

int main()
{
	treenode *n1 = createnode(10);
	treenode *n2 = createnode(11);
	treenode *n3 = createnode(12);
	treenode *n4 = createnode(13);
	treenode *n5 = createnode(14);

	n1->left = n2;
	n1->right = n3;
	n3->left = n4;
	n3->right = n5;

	printtree(n1);

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
}