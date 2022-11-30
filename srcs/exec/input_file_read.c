#include "ft_21sh.h"

static int	open_read_check(char *filename)
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

void	input_file_read(char *filename)
{
	char	buf[4096];
	int		file_fd;
	ssize_t	ret;

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
	exit(14);
}

