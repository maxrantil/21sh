#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	char	**args;
	char	*command;
	int		type;			// 1 exec, 2 pipe
}	t_node;

void	exec_command(t_node *node, char **env);
int	ft_strarray_size(char **arr);
char	**copy_double_array(char **env);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_free_doublearray(char ***array);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	init_nodes(t_node *eleft, t_node *eright, t_node *pipe, t_node *last, t_node *cent);
void	exec_pipe_node(t_node *node, char **env);

int main(void)
{
	extern char **environ;
	t_node		center;
	t_node		last;
	t_node		right;
	t_node		left;
	t_node		pipe;
	t_node		*head;
	/*
		last (3)
	cent
			right (2)
		pipe
			left (1)
	*/

	head = &center;			// test with 3 pipes (ls | grep | wc)
	// head = &pipe;		// test with 2 pipes (ls | grep)
	init_nodes(&left, &right, &pipe, &last, &center);

	int pid = fork();
	if (pid == -1)
	{
		printf("error fork\n");
		exit(1);
	}
	else if (pid == 0)
	{
		exec_command(head, environ);
	}
	wait(&pid);
	ft_free_doublearray(&(right.args));
	ft_free_doublearray(&(left.args));
	ft_free_doublearray(&(last.args));
	return (123);
}

void	exec_pipe_node(t_node *node, char **env)
{
	int	p[2];

	pipe(p);
	if (fork() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		exec_command(node->left, env);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		exec_command(node->right, env);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	exit(3);
}

void	exec_command(t_node *node, char **env)
{

	if (node == NULL)
	{
		exit(2);
	}
	if (node->type == 1)
	{
		if (execve(node->command, node->args, env) == -1)
		{
			write(2, "error with execve\n", 18);
			exit(1);
		}
	}
	else if (node->type == 2)
	{
		exec_pipe_node(node, env);
	}
}

void	init_nodes(t_node *left, t_node *right, t_node *pipe, t_node *last, t_node *cent)
{
	char *arr[] = {"ls", "-Rl", "/Users/rvuorenl", NULL};
	char *arr2[] = {"grep", "main.c", NULL};
	char *arr3[] = {"wc", "-l", NULL};

	left->right = NULL;
	left->left = NULL;
	left->args = copy_double_array(arr);
	left->command = "/bin/ls";
	left->type = 1;

	right->right = NULL;
	right->left = NULL;
	right->args = copy_double_array(arr2);
	right->command = "/usr/bin/grep";
	right->type = 1;

	pipe->right = right;
	pipe->left = left;
	pipe->args = NULL;
	pipe->type = 2;

	last->right = NULL;
	last->left = NULL;
	last->args = copy_double_array(arr3);
	last->command = "/usr/bin/wc";
	last->type = 1;

	cent->left = pipe;
	cent->right = last;
	cent->args = NULL;
	cent->type = 2;
}

int	ft_strarray_size(char **arr)
{
	int	i;

	if (!arr || !arr[0])
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**copy_double_array(char **env)
{
	char	**env_copy;
	int		env_size;

	env_size = ft_strarray_size(env);
	env_copy = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env_copy)
		exit(4);
	env_copy[env_size--] = NULL;
	while (env_size >= 0)
	{
		env_copy[env_size] = ft_strdup(env[env_size]);
		env_size--;
	}
	return (env_copy);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = (char *) malloc(sizeof(*s2) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

void	ft_strdel(char **as)
{
	if (as == NULL)
		return ;
	ft_strclr(*as);
	free(*as);
	*as = NULL;
}

void	ft_strclr(char *s)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		s[i] = '\0';
		i++;
	}
}
