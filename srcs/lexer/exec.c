#include "temp.h"

int	dup2_check(int file_fd, int old_fd)
{
	int	dup2_fd;

	dup2_fd = dup2(file_fd, old_fd);
	if (dup2_fd == -1)
	{
		write(2, "error on dup2_check\n", 20);
		exit(11);
	}
	return (dup2_fd);
}

void	input_file_read(char *filename)
{
	char	buf[4096];
	int		file_fd;
	int		ret;

	file_fd = open_read_check(filename);
	ret = read(file_fd, buf, 4095);
	while (ret > 0)
	{
		buf[ret] = '\0';
		write(1, buf, ft_strlen(buf));
		ft_strclr(buf);
		ret = read(file_fd, buf, 4095);
	}
	close(file_fd);
	exit(11);
}

int	open_read_check(char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		// check reason ?
		write(2, "open_read fail\n", 15);
		exit(1);
	}
	return (file_fd);
}

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
	if (file_fd == -1)
	{
		write(2, "error on open_mode\n", 19);
		exit(10);
	}
	return (file_fd);
}

void	redirection_file(t_node *node)
{
	int file_fd;
	int	dup2_fd;

		// check if (!node->right), SEGFAULT?
	file_fd = open_check(node->arg[0], node->type);	//	1 == > , 2 == >>
	dup2_fd = dup2_check(file_fd, 1);
	if (fork_check() == 0)
	{
		exec_tree(node->left);
	}
	wait(0);
	close(file_fd);
	exit(7);
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
	else if (node->type == REDIROVER || node->type == REDIRAPP)
		redirection_file(node);
	else if (node->type == REDIRIN)
		input_file_read(node->arg[0]);
	else if (node->type == AMP)
	{
		if (fork_check() == 0)
			exec_tree(node->left);
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