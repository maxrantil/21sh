#include "temp.h"
#include "../../libft/includes/libft.h"
#include "../../libft/includes/get_next_line.h"


int	count_output_lines(int fd)
{
	int		lines;
	char	*str;

	lines = 0;
	while (get_next_line(fd, &str) > 0)
	{
		lines++;
		// printf("%s\n", str);
		// write(1, str, ft_strlen(str));
		ft_strdel(&str);
	}
	return (lines);
}

// int	write_to_temp(t_node *root)
// {
// 	int	fd;
// 	int	p[2];

// 	fd = open(".temp_gnl", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		write(2, "Error opening .temp_gnl\n", 24);
// 		exit(2);
// 	}
// }

void	write_to_temp(t_node *root)
{
	int file_fd;
	int	dup2_fd;
	int	lines;

	lines = 0;
	file_fd = open_check(".temp_gnl", REDIROVER);
	dup2_fd = dup2_check(file_fd);
	if (fork_check() == 0)
	{
		exec_tree(root);
	}
	wait(0);
	lines = count_output_lines(file_fd);
	// printf("lines = (%d)\n", lines);
	close(file_fd);
	exit(7);
}
