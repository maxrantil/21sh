#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREE 0
#define MULT 1
#define DIV 2
#define ADD 3
#define SUB 4
#define NEG 5
#define INT 6

#define COUNT 10

typedef struct s_tree
{
	int	type;
	int	value;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

t_tree *create_treenode(int	type, int value, t_tree *left, t_tree *right)
{
	t_tree *node = (t_tree *)malloc(sizeof(t_tree));
	if (node != NULL) 
	{
		node->type = type;
		node->value = value;
		node->left = left;
		node->right = right;
	}
	return node;
}

/* void print_tree(t_tree *tree)
{
	if (tree->type == INT)
	{
		printf("%d", tree->value - '0');
		return ;
	}
	printf("(");
	if (tree->type == MULT)
	{
		print_tree(tree->left);
		printf(" * ");
		print_tree(tree->right);	
	}
	else if (tree->type == DIV)
	{
		print_tree(tree->left);
		printf(" / ");
		print_tree(tree->right);	
	}
	else if (tree->type == ADD)
	{
		print_tree(tree->left);
		printf(" + ");
		print_tree(tree->right);	
	}
	else if (tree->type == SUB)
	{
		print_tree(tree->left);
		printf(" - ");
		print_tree(tree->right);	
	}
	printf(")");
} */

int	eval_tree(t_tree *tree)
{
		/* printf("LEFT: %p\n", tree->left); */
	if (tree->type == INT)
		return (tree->value - '0');
	else if (tree->type == MULT)
		return (eval_tree(tree->left) * eval_tree(tree->right));
	else if (tree->type == DIV)
		return (eval_tree(tree->left) / eval_tree(tree->right));
	else if (tree->type == ADD)
		return (eval_tree(tree->left) + eval_tree(tree->right));
	else if (tree->type == SUB)	
		return (eval_tree(tree->left) - eval_tree(tree->right));
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	scan_token(char **argv)
{
	char token;
	int  ret;

	if (**argv == '\0')
		return (0);
	ret = 0;
	token = **argv;
	if (strchr("+-*()", token))
	{
		++(*argv);
		ret = token;
	}
	else if (ft_isdigit(token))
	{
		++(*argv);
		ret = token;
	}
	else
	{
		printf("Error: scan_token() invalid token: %c\n", token);
		exit(1);
	}
	return (ret);
}

t_tree *parse_e(int token, char **argv);
t_tree *parse_t(int token, char **argv);
t_tree *parse_f(int token, char **argv);

// GRAMMAR E -> T{+|- T}
t_tree *parse_e(int token, char **argv) 
{
	t_tree *a;
	t_tree *b;
	t_tree *c;

	c = NULL;
	b = NULL;
	a = parse_t(token, argv);
	while (1)
	{
		if (*argv[1] == '+')
		{
			token = scan_token(&argv[1]);
			b = parse_t(token, argv);
			a = create_treenode(ADD, 0, a, b);
		}
		else if (*argv[1] == '-')
		{
			token = scan_token(&argv[1]);
			b = parse_t(token, argv);
			a = create_treenode(SUB, 0, a, b);
		}
		else
			return (a);	
	}
	return (a);
}

// GRAMMAR T -> F{*|/ F}	
t_tree *parse_t(int token, char **argv) 
{
	t_tree *a;
	t_tree *b;
	t_tree *c;

	c = NULL;
	b = NULL;
	a = parse_f(token, argv);
	while (1)
	{
		if (*argv[1] == '*')
		{
			token = scan_token(&argv[1]);
			b = parse_f(token, argv);
			a = create_treenode(MULT, 0, a, b);
		}
		else if (*argv[1] == '/')
		{
			token = scan_token(&argv[1]);
			b = parse_f(token, argv);
			a = create_treenode(DIV, 0, a, b);
		}
		else
			return (a);	
	}
	return (a);
}

// GRAMMAR F -> Integer
t_tree *parse_f(int token, char **argv)
{
	if (ft_isdigit(token))
	{
		return (create_treenode(INT, token, NULL, NULL));
	}
	else if (ft_isdigit(*argv[1]))
	{
		token = scan_token(&argv[1]);
		return (create_treenode(INT, token, NULL, NULL));
	}
	else  
		return (NULL);
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
	if (root->type == INT)
		printf("%d\n", root->value - '0');
	else if (root->type == MULT)
		printf("*");
	else if (root->type == DIV)
		printf("/");
	else if (root->type == ADD)
		printf("+");
	else if (root->type == SUB)
		printf("-");
	else if (root->type == NEG)
		printf("-");
	printtree_rec(root->left, lvl);
}

void print_tree(t_tree *root) 
{
	printtree_rec(root, 0);
}

int main(int argc, char **argv)
{
	int		token;
	t_tree	*result_tree;

	token = scan_token(&argv[1]);
	if (token == 0)
	{
		printf("Error: main() invalid token: %c\n", token);
		exit(1);
	}
	result_tree = parse_e(token, argv);
	print_tree(result_tree);
	printf("Result = %d\n", eval_tree(result_tree));
	
	return (0);
}
// -(7 + 5) * 2
//	    *
//	   / \
//	  -   2
//	 / \
//	7   5 
	/* t_tree *root = create_multnode(MULT, NULL, NULL);
	t_tree *neg = create_negnode(NEG, NULL);
	t_tree *int5 = create_intnode(INT, 5);
	t_tree *int2 = create_intnode(INT, 2); */