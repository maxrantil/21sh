#include "temp.h"

// one backslag take it away, two backslshes keep one. last newline is always changes to \0
char *lexer(char *str)
{
	int i = 0;
	int j = 0;
	char *new;

	new = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		new[j++] = str[i++];
	}
	new[j - 1] = '\0';
	return (new);
}

int	dup2_check2(int file_fd, int old_fd)
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

int	check_filename_fd(char *filename)
{
	int	i;

	i = -1;
	while(filename[++i])
	{
		if (!ft_isdigit(filename[i]))
			return (0);
	}
	return (1);
}

//	2 > filename   		->	  	  (filename, 2)
//	2 >& 1   		->	  	      (1, 2)
void	open_redirect_stream(char *filename, int old_fd)
{
	int	fd;

	if (check_filename_fd(filename))
	{
		fd = ft_atoi(filename);
	}
	// else if ()	// check whether > or >>
	// {
	// 	fd = open_check(filename, REDIRAPP);
	// 	2 >> filename
	// }
	else
	{
		fd = open_check(filename, REDIROVER);
		// 2 > filename
	}
	dup2_check2(fd, old_fd);
}

int main()
{
	// char	*str = "ps aux | grep mrantil | grep -v grep | grep 8 | wc -l";
	// char	*str = "cat < 2.txt | grep t > 1.txt";
	// char *str = "cat file | grepp ssd ";
	// char *str = "echo hello | grep h > text.txt ; cat text.txt ; echo again";
	// char *str = "echo try > to_me again";
	// char *str = "echo hello ; echo world";
	// char *str = "echo tjotjo > file ; cat < file > file2";
	// char *str = "cat < file | grep t > file2";
	// char *str = "echo $PWD ; cd .. ; echo $PWD";
	// char *str = "echo hello\n"; //echo hello\0
	// char *str = "echo \'hello\n"; //echo 'hello\0
	// char *str = "echo \\hello\n"; //echo \hello\0
	// char *str = "echo \\nhello\n";
	// char *str = "echo '\nhello\nagain'\n";
	// char *str = "echo \nhello\nagain\n";
	// char *str = "echo hello\again'\n"; // echo helloagain\0
	// one backslag take it away, two backslshes keep one. last newline is always changes to \0
	char *str = "ls file non_exist";
	t_node	*root;
	// str = lexer(str);
	// printf("%s\n", str);
	root = parse_line(&str); //make a loop and check for str != NULL and if you encouunter redir in string break out and set it to new root here

	// print_tree(root);
	// write(1, "\n", 1);
	if (fork_check() == 0)
	{
		// open_redirect_stream("/dev//null", 2);
		open_redirect_stream("err_file", 2);
		exec_tree(root);
	}
	wait(0);
	exit(0);
}
