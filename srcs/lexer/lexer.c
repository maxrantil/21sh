#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define COUNT 10
#define EXEC 1
#define PIPE 2

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (&((char *)s)[i]);
	return (NULL);
}

static int	ft_isspace(const char *str)
{
	if ((*str >= 9 && *str <= 13) || *str == 32)
		return (1);
	return (0);
}

static char	*skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr) && *ptr)
		ptr++;
	return (ptr);
}

static char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = (char *)malloc(sizeof(char) * len + 1);
	if (!ss)
		return (NULL);
	while (len--)
		ss[i++] = s[start++];
	ss[i] = '\0';
	return (ss);
}


int	peek(char **ps, char *toks)
{
	char *p;

	p = *ps;
	while (*p && ft_isspace((const char *)p))
		p++;
	*ps = p;
	return (*p && ft_strchr(toks, *p));
}

int	get_token(char **s, char **token, char **end_q)
{
	char	*p;
	int		ret;
	
	p = *s;
	p = skip_whitespaces(p);
	if (*p == '\0')
		return (0);
	if (token)
		*token = p;
	ret = *p;
	while (*p)
	{
		if (strchr("<|&;", *p) && p++)
			break ;
		else if (*p == '>' && p++)
		{
			if (*p == '>' && p++)
				ret = '#';
			break ;
		}
		else
		{
			ret = 'a';
			while (*p && !ft_isspace(p) && !strchr("<|&;>", *p))
				p++;
			break ;
		}
	}
	if (end_q)
		*end_q = p;
	p = skip_whitespaces(p);
	*s = p;
	return (ret);
}

typedef struct s_node
{
	int				type;
	char			*exec[100];
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

t_node	*create_node(int type, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node != NULL)
	{
		memset(node, 0, sizeof(t_node));
		node->type = type;
		node->left = left;
		node->right = right;
	}
	return (node);
}

t_node *parse_exec(char **str)
{
	char *token;
	char *end_q;
	size_t	t = 0;
	t_node *node;

	node = create_node(EXEC, NULL, NULL);
	while (**str && !peek(str, "<|&>#;"))
	{
		int ret = get_token(str, &token, &end_q);
		if (ret == 'a')
		{
			node->exec[t] = ft_strsub(token, 0, end_q - token);
			t++;
		}	
	}
	node->exec[t] = NULL;
	return (node);
}

t_node	*parse_pipe(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	t_node	*node;

	node = parse_exec(ptr_to_str);
	if (peek(ptr_to_str, "|"))
	{
		get_token(ptr_to_str, &token, &end_q);
		node = create_node(PIPE, node, parse_pipe(ptr_to_str));
	}
	return (node);
}

t_node	*parse_line(char **ptr_to_str)
{
	t_node	*node;

	node = parse_pipe(ptr_to_str);
	return (node);
}

t_node *parse_cmd(char *str)
{
	t_node	*node;

	node = parse_line(&str);
	return (node);
}

void run_cmd(t_node *node)
{
	int p[2];

	if (!node)
		exit(1);
	if (node->type == EXEC)
	{
		if (!node->exec[0])
			exit(1);
		execvp(node->exec[0], node->exec);
		write(1, "ERROR EXEC\n", 11);
	}
	else
	{
		if (pipe(p) < 0)
		{
			write(1, "pipe error\n", 11);
			exit(1);
		}	
		if (fork() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			run_cmd(node->left);
		}
		if (fork() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			run_cmd(node->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	exit(0);
}

void	printtree_rec(t_node *root, int lvl)
{
	if (root == NULL)
		return ;
	lvl += COUNT;
	printtree_rec(root->right, lvl);
	printf("\n");
	for (int i = COUNT; i < lvl; i++)
		printf(" ");
	if (root->type == EXEC)
		printf("%s\n", root->exec[0]);
	else if (root->type == PIPE)
		printf("|");
	printtree_rec(root->left, lvl);
}

void print_tree(t_node *root) 
{
	printtree_rec(root, 0);
}

int main()
{
	char	*str = "ls -la -F | grep a.out";
	t_node *node;
	node = parse_cmd(str);
	print_tree(node);
	run_cmd(node);
	exit(0);
}