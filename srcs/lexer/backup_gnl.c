#include "temp.h"

int	count_output_lines(int fd)
{
	int		lines;
	char	*str;

	lines = 0;
	while (get_next_line(fd, &str) != -1)
	{
		lines++;
		printf("%s\n", str);
		// write(1, str, ft_strlen(str));
		ft_strdel(&str);
	}
	return (lines);
}
