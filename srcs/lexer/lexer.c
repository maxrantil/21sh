#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define COUNT 10
#define EXEC 1
#define PIPE 2
#define REDIR 3

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


int	peek(char **ptr_to_str, char *toks)
{
	char *p;

	p = *ptr_to_str;
	while (*p && ft_isspace((const char *)p))
		p++;
	*ptr_to_str = p;
	return (*p && ft_strchr(toks, *p));
}

static int token_loop(char **p, int ret)
{
	while (**p)
	{
		if (strchr("<|&;", **p) && (*p)++)
			break ;
		else if (**p == '>' && (*p)++)
		{
			if (**p == '>' && (*p)++)
				ret = '#';
			break ;
		}
		else
		{
			ret = 'a';
			while (**p && !ft_isspace(*p) && !strchr("<|&;>", **p))
				(*p)++;
			break ;
		}
	}
	return (ret);
}

int	get_token(char **ptr_to_str, char **token, char **end_q)
{
	char	*p;
	int		ret;
	
	p = *ptr_to_str;
	p = skip_whitespaces(p);
	if (*p == '\0')
		return (0);
	if (token)
		*token = p;
	ret = *p;
	ret = token_loop(&p, ret);
	if (end_q)
		*end_q = p;
	p = skip_whitespaces(p);
	*ptr_to_str = p;
	return (ret);
}

typedef struct s_node
{
	int				type;
	char			*arg[100];
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_root
{
	t_node	*root;
}				t_root;

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
			node->arg[t] = ft_strsub(token, 0, end_q - token);
			t++;
		}
		/* else if (ret == '>')
			node = create_node(REDIR, NULL, node); */
	}
	node->arg[t] = NULL;
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

void	exec_command(t_node *node);
void	exec_pipe_node(t_node *node);

int	fork_check(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "error on fork\n", 14);
		exit(1);
	}
	return (pid);
}

void	exec_pipe_node(t_node *node)
{
	int	p[2];

	if (pipe(p) < 0)
	{
		printf("pipe\n");
		exit(1);
	}
	if (fork_check() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		exec_command(node->left);
	}
	if (fork_check() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		exec_command(node->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	exit(3);
}

int	open_check(char *filename, int mode)
{
	int	file_fd;

	file_fd = -1;
	if (mode == 1)	// overwrite/create >
	{
		// file_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
		file_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (mode == 2)	// append/create >>
	{
		// file_fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
		file_fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	if (file_fd == -1)
	{
		write(2, "error on open_mode\n", 19);
		exit(10);
	}
	return (file_fd);
}

int	dup2_check(int file_fd)
{
	int	dup2_fd;

	dup2_fd = dup2(file_fd, 1);
	if (dup2_fd == -1)
	{
		write(2, "error on dup2_check\n", 20);
		exit(11);
	}
	return (dup2_fd);
}

void	redirection_file(t_node *node)
{
	int file_fd;
	int	dup2_fd;

		// check if (!node->right), SEGFAULT?
	file_fd = open_check(node->left->arg[0], 1);	//	1 == > , 2 == >>

	// printf("STR: %s\n", node->right->arg[0]);
	write(2, "STR: ", 5);
	dup2_fd = dup2_check(file_fd);
	if (fork_check() == 0)
	{
		exec_command(node->right);
	}
	wait(0);
	close(file_fd);
	exit(7);
}

void	exec_command(t_node *node)
{
	int p[2];

	if (!node)
		exit(1);
	if (node->type == EXEC)
	{
		if (!node->arg[0])
			exit(1);
		execvp(node->arg[0], node->arg);
		write(1, "ERROR EXEC\n", 11);
	}
	else if (node->type == PIPE)
		exec_pipe_node(node);
	/* else if (node->type == REDIR)
		redirection_file(node); */
	exit(0);
}

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
		printf("%s\n", root->arg[0]);
	else if (root->type == PIPE)
		printf("|");
	rec_print_tree(root->left, lvl);
}

void print_tree(t_node *root) 
{
	rec_print_tree(root, 0);
}

int main()
{
	// char	*str = "ps aux | grep mrantil | grep -v grep | grep 8 | wc -l";
	char	*str = "ls | grep a.out | wc -l";
	t_node	*root;

	root = parse_line(&str);
	print_tree(root);
	exec_command(root);
	exit(0);
}