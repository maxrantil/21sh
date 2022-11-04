#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define COUNT 10
#define EXEC 1
#define PIPE 2
#define REDIROVER 3 // >
#define REDIRAPP 4 // >>
#define REDIRIN 5 // <
#define AMP 6
#define SEMI 7

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

static int token_loop(char **p, int ret) //retname p to s
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
	char	*p; //rename to scan
	int		ret;

	p = *ptr_to_str; //rename to inputptr
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
	struct s_node	*command;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

t_node	*create_node(int type, t_node *sub_cmd, t_node *left, t_node *right)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = type;
	node->command = sub_cmd;
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*parse_redirection(t_node *node, char **str)
{
	char	*token;
	char	*end_q;
	int		type;

	while (peek(str, "<>"))
	{
		type = get_token(str, &token, 0);
		if (get_token(str, &token, &end_q) != 'a')
		{
			printf("syntax error near unexpected token `redirect'\n");
			exit(1);
		}
		//if here: token == file name
		if (type == '>')
		{
			node = create_node(REDIR, node, NULL, NULL);
			node->arg[0] = ft_strsub(token, 0, end_q - token);
		}
	}
	return (node);
}

t_node *parse_exec(char **ptr_to_str)
{
	char	*token;
	char	*end_q;
	int		type;
	size_t	argc;
	t_node	*node;

	node = create_node(EXEC, NULL, NULL, NULL);
	node = parse_redirection(node, ptr_to_str);
	argc = 0;
	while (**ptr_to_str && !peek(ptr_to_str, "|&;"))
	{
		type = get_token(ptr_to_str, &token, &end_q);
		if (type == 'a')
			node->arg[argc++] = ft_strsub(token, 0, end_q - token);
		else if (type == 0)
			break ;
		else
		{
			printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
		node = parse_redirection(node, ptr_to_str);
	}
	node->arg[argc] = NULL;
	return (node);
}

t_node	*parse_pipe(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	int		type;
	t_node	*node;

	node = parse_exec(ptr_to_str);
	if (peek(ptr_to_str, "|"))
	{
		type = get_token(ptr_to_str, &token, &end_q);
		if (!peek(ptr_to_str, "|&;"))
			node = create_node(PIPE, NULL, node, parse_pipe(ptr_to_str));
		else
		{
			printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
	}
	return (node);
}

t_node	*parse_line(char **ptr_to_str)
{
	char 	*token;
	char 	*end_q;
	t_node	*node;

	node = parse_pipe(ptr_to_str);
	if (peek(ptr_to_str, "&"))
	{
		get_token(ptr_to_str, &token, &end_q);
		node = create_node(AMP, node, NULL, NULL);
	}
	else if (peek(ptr_to_str, ";"))
	{
		get_token(ptr_to_str, &token, &end_q);
		node = create_node(SEMI, NULL, node, parse_line(ptr_to_str));
	}
	if (peek(ptr_to_str, ""))
	{
		printf("syntax error near unexpected token `newline'\n");
		exit(1);
	}
	return (node);
}

void	exec_tree(t_node *node);
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
		write(2, "error on pipe\n", 14);
		exit(1);
	}
	if (fork_check() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		exec_tree(node->left);
	}
	if (fork_check() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		exec_tree(node->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

int	open_check(char *filename, int mode)
{
	int	file_fd;

	file_fd = -1;
	if (mode == REDIROVER) // >
		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == REDIRAPP) // >>
		file_fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (mode == REDIRIN) // <
	if (file_fd == -1)
	{
		write(2, "error on open_mode\n", 19);
		exit(10);
	}
	return (file_fd);
}

void	redirection_file(t_node *node)
{
	close(1);
	dup(open_check(node->arg[0], node->type));	//	1 == > , 2 == >>
	exec_tree(node->command);
}

void	exec_tree(t_node *node)
{
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
	else if (node->type == REDIRIN || node->type == REDIROVER || node->type == REDIRAPP)
		redirection_file(node);
	else if (node->type == AMP)
	{
		if (fork_check() == 0)
			exec_tree(node->command);
	}
	else if (node->type == SEMI)
	{
		if (fork_check() == 0)
			exec_tree(node->left);
		wait(0);
		exec_tree(node->right);
	}
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
	{
		if (root->arg[2])
			printf("%s %s ...\n", root->arg[0], root->arg[1]);
		else if (root->arg[1])
			printf("%s %s\n", root->arg[0], root->arg[1]);
		else
			printf("%s\n", root->arg[0]);
	}
	else if (root->type == PIPE)
		printf("|");
	else if (root->type == REDIR)
	{
		if (root->command->arg[2])
			printf("%s %s ... > %s\n", root->command->arg[0], root->command->arg[1], root->arg[0]);
		else if (root->command->arg[1])
			printf("%s %s > %s\n", root->command->arg[0], root->command->arg[1], root->arg[0]);
		else
			printf(" %s > %s\n", root->command->arg[0], root->arg[0]);
	}
	else if (root->type == AMP)
		printf("&");
	else if (root->type == SEMI)
		printf(";");
	rec_print_tree(root->left, lvl);
}

void print_tree(t_node *root)
{
	rec_print_tree(root, 0);
}

int main()
{
	// char	*str = "ps aux | grep mrantil | grep -v grep | grep 8 | wc -l";
	char	*str = "echo hello | grep h > test.txt";
	// char *str = "echo hello | grep h > text.txt ; cat text.txt ; echo again";
	// char *str = "echo try > to_me again";
	// char *str = "echo hello ; echo world";
	t_node	*root;

	root = parse_line(&str); //make a loop and check for str != NULL and if you encouunter redir in string break out and set it to new root here
	print_tree(root);
	write(1, "\n", 1);
	exec_tree(root);
	exit(0);
}