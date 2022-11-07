#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	char	**args;
	char	*command;
	int		type;			// 1 exec, 2 pipe, 3 redirect
}	t_node;

int	ft_strarray_size(char **arr);
char	**copy_double_array(char **env);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_free_doublearray(char ***array);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	exec_command(t_node *node, char **env);

void	init_nodes(t_node *left, t_node *right, t_node *cent)
{
	char *arr[] = {"cat", "random.txt", NULL};

	left->right = NULL;
	left->left = NULL;
	left->args = copy_double_array(arr);
	left->command = "/bin/cat";
	left->type = 1;

	right->right = NULL;
	right->left = NULL;
	right->args = NULL;
	right->command = "testfile.txt";
	right->type = 0;

	cent->left = left;
	cent->right = right;
	cent->args = NULL;
	cent->type = 3;
}
/*			file
	redir
			cat
*/

int	fork_check(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "error on fork\n", 14);
		exit(8);
	}
	return (pid);
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

void	redirection_file(t_node *node, char **env)
{
	int file_fd;
	int	dup2_fd;

		// check if (!node->right), SEGFAULT?
	file_fd = open_check(node->right->command, 1);	//	1 == > , 2 == >>
	dup2_fd = dup2_check(file_fd);
	if (fork_check() == 0)
	{
		exec_command(node->left, env);
	}
	wait(0);
	close(file_fd);
	exit(7);
}

void	exec_command(t_node *node, char **env)
{

	if (node == NULL)
	{
		exit(2);
	}
	if (node->type == 0)
		exit(6);
	if (node->type == 1)
	{
		if (execve(node->command, node->args, env) == -1)
		{
			// add reason for fail?
			write(2, "error with execve\n", 18);
			exit(1);
		}
	}
	// else if (node->type == 2)
	// {
	// 	exec_pipe_node(node, env);
	// }
	else if (node->type == 3)
	{
		redirection_file(node, env);
	}
}

int main(void)
{
	extern char **environ;
	t_node		center;
	t_node		right;
	t_node		left;
	t_node		*head;
	int			pid;

	init_nodes(&left, &right, &center);
	head = &center;
	pid = fork_check();
	if (pid == 0)
	{
		exec_command(head, environ);
	}
	wait(&pid);
	ft_free_doublearray(&(left.args));
	return (51);
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