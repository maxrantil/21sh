#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	t_tree *n = (t_tree *)malloc(sizeof(t_tree));
	if (n != NULL)
	{
		n->type = type;
		n->value = value;
		n->left = left;
		n->right = right;
	}
	return n;
}

int	eval_tree(t_tree *tree)
{
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

int	scan_tok(char **next_tok)
{
	char tok;
	int  ret;

	if (**next_tok == '\0')
		return (0);
	ret = 0;
	tok = **next_tok;
	if (strchr("+-*/", tok))
	{
		++(*next_tok);
		ret = tok;
	}
	else if (ft_isdigit(tok))
	{
		++(*next_tok);
		ret = tok;
	}
	else
	{
		printf("Error: scan_tok() invalid tok: %c\n", tok);
		exit(1);
	}
	return (ret);
}

t_tree *parse_e(int tok, char **next_tok);
t_tree *parse_t(int tok, char **next_tok);
t_tree *parse_f(int tok, char **next_tok);

// GRAMMAR E -> T{+|- T}
t_tree *parse_e(int tok, char **next_tok)
{
	t_tree *a;
	t_tree *b;
	t_tree *c;

	c = NULL;
	b = NULL;
	a = parse_t(tok, next_tok);
	while (1)
	{
		if (*next_tok[1] == '+')
		{
			tok = scan_tok(&next_tok[1]);
			b = parse_t(tok, next_tok);
			a = create_treenode(ADD, 0, a, b);
		}
		else if (*next_tok[1] == '-')
		{
			tok = scan_tok(&next_tok[1]);
			b = parse_t(tok, next_tok);
			a = create_treenode(SUB, 0, a, b);
		}
		else
			return (a);
	}
	return (a);
}

// GRAMMAR T -> F{*|/ F}
t_tree *parse_t(int tok, char **next_tok)
{
	t_tree *a;
	t_tree *b;
	t_tree *c;

	c = NULL;
	b = NULL;
	a = parse_f(tok, next_tok);
	while (1)
	{
		if (*next_tok[1] == '*')
		{
			tok = scan_tok(&next_tok[1]);
			b = parse_f(tok, next_tok);
			a = create_treenode(MULT, 0, a, b);
		}
		else if (*next_tok[1] == '/')
		{
			tok = scan_tok(&next_tok[1]);
			b = parse_f(tok, next_tok);
			a = create_treenode(DIV, 0, a, b);
		}
		else
			return (a);
	}
	return (a);
}

// GRAMMAR F -> Integer //? | (E) ?
t_tree *parse_f(int tok, char **next_tok)
{
	if (ft_isdigit(tok))
	{
		return (create_treenode(INT, tok, NULL, NULL));
	}
	else if (ft_isdigit(*next_tok[1]))
	{
		tok = scan_tok(&next_tok[1]);
		return (create_treenode(INT, tok, NULL, NULL));
	}
	else
		return (NULL);
}

void print_tree2(t_tree *tree)
{
	if (tree->type == INT)
	{
		printf("%d", tree->value - '0');
		return ;
	}
	printf("(");
	if (tree->type == MULT)
	{
		print_tree2(tree->left);
		printf(" * ");
		print_tree2(tree->right);
	}
	else if (tree->type == DIV)
	{
		print_tree2(tree->left);
		printf(" / ");
		print_tree2(tree->right);
	}
	else if (tree->type == ADD)
	{
		print_tree2(tree->left);
		printf(" + ");
		print_tree2(tree->right);
	}
	else if (tree->type == SUB)
	{
		print_tree2(tree->left);
		printf(" - ");
		print_tree2(tree->right);
	}
	printf(")");
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

void tree_print(t_tree *root)
{
	printtree_rec(root, 0);
}

int main(int argc, char **argv)
{
	int		tok;
	t_tree	*result_tree;

	tok = scan_tok(&argv[1]);
	if (tok == 0)
	{
		printf("Error: main() invalid tok: %c\n", tok);
		exit(1);
	}
	result_tree = parse_e(tok, argv);
	tree_print(result_tree);
	write(1, "\n", 1);
	print_tree2(result_tree);
	printf(" = %d\n", eval_tree(result_tree));
	return (0);
}
