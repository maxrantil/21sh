#include "ft_21sh.h"
// #include "../../libft/includes/libft.h"

// #include <sys/stat.h>				//	*	*	*	*	*

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

// int	open_check(char *filename, int mode)
// {
// 	int	file_fd;

// 	file_fd = -1;
// 	if (mode == REDIROVER) // >
// 		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (mode == REDIRAPP) // >>
// 		file_fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
// 	if (file_fd == -1)
// 	{
// 		write(2, "error on open_mode\n", 19);
// 		exit(10);
// 	}
// 	return (file_fd);
// }

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

//	2 > filename   		->	  	  (filename, 2)
//	2 >& 1   		->	  	      (1, 2)
//filename = target
//old_fd = fd redirected
void	open_redirect_stream(char *filename, char *old_fd, int mode)
{
	int	target_fd;
	int	redir_fd;

	if (filename)
	{
		if (check_filename_fd(filename))
			target_fd = ft_atoi(filename);
		else if (mode == REDIRAPP)
			target_fd = open_check(filename, REDIRAPP);
		else
			target_fd = open_check(filename, REDIROVER);
	}
	else
	{
		printf("Syntax error!\n");
		exit(0);
	}
	redir_fd = ft_atoi(old_fd);
	dup2_check2(target_fd, redir_fd);
}
// int	dup2_check2(int file_fd, int old_fd)

void	close_fd(char *fd_str)
{
	int	fd;

	fd = ft_atoi(fd_str);
	close(fd);
}

void	syntax_error_msg(int exit_code)
{
	printf("Syntax error!\n");					// PRINTF
	exit(exit_code);
}

//	&>
//	>&
// 	|&
// 	>&-

void	check_fd_syntax(char *full)
{
	int	i;

	i = -1;
	while (full[++i])
	{
		while (full[i] && ft_isdigit(full[i]))
			i++;
		if (full[i] != '>' || full[i] != '|' || full[i] != '&')
			syntax_error_msg(8);
		return ;
	}
}

/*	return fd, or if not found, default 1	*/
int	get_redirected_fd(char *full)
{
	int	fd;

	fd = ft_atoi(full);
	if (fd == 0)
		return (1);
	return (fd);
}

/*	return '>&' from full '1>&filename' 	*/
char	*get_redirect_operator(char *full)
{
	int	i;
	int	len;

	i = 0;
	while (full[i])
	{
		while (full[i] != '>' && full[i] != '|' && full[i] != '&' && full[i])
			i++;
		len = i;
		while (full[len] == '>' || full[len] == '|' || full[len] == '&'
				|| full[len] == '-')
			len++;
		len -= i;
		return (ft_strsub(full, i, (size_t)len));
	}
	return (ft_strdup(""));
}

/*	return 'filename' from full '1>&filename'
	if not found (1>&), take arg+1 (1>& filename)
	*/
char	*get_target_file(char *full, char *filename, size_t oper_len)
{
	size_t	target_len;
	size_t	i;

	i = 0;
	while (full[i] != '>' && full[i] != '|' && full[i] != '&' && full[i])
		i++;

	// i = len of everything before first operator-char
	// 1>filename (i = 1)
	//  full_len = 10
	// 	oper_len = 1
	// 	target_len = 8
	// 	i = 1 (fd_len)

	target_len = ft_strlen(full) - oper_len - i;
	if (target_len == 0)
	{
		if (filename)
			return (ft_strdup(filename));
		syntax_error_msg(9);
	}
	else
		return (ft_strsub(full, i + oper_len, target_len));
	return (NULL);
}

void	check_ambiguous_redirect(int fd, char *target)
{
	if (fd != 1)
	{
		if (!check_filename_fd(target))
		{
			printf("21: %s: ambiguous redirect\n", target);		// printf
			// printf("exit 6\n");
			exit(6);
		}
	}
}

void	check_bad_fd(int file_fd, char *filename)
{
	struct stat	buf;
	int			ret;

	ret = fstat(file_fd, &buf);
	if (ret == -1)
	{
		printf("21: %s: Bad file desctiptor\n", filename);
		// printf("error 5 with (%d)\n", file_fd);
		exit(5);
	}
	// else
	// {
	// 	printf("%d OK\n", file_fd);
	// }
}

void	check_operator_errors(int file_fd, char *filename, char *operator)
{
	if ((!filename) && (!ft_strequ(operator, ">&-")))
		// printf("\tSYNTAX\n");
		syntax_error_msg(10);

	check_ambiguous_redirect(file_fd, filename);
	check_bad_fd(file_fd, filename);
}

// only if '&' found
void	check_file_aggregations(char *full, char *filename)
{
		// full = 2>&1
		// full = >&1
		// full = 2>& 1
		// full = &>filename
		// full = &> filename
	int		file_fd;		// stuff before &>
	char	*operator;		// &>
	char	*target_file;	// where to redirect, if filename NULL (next arg[])
	int		target_fd;		// filenames fd, or fd if is_num

	file_fd = get_redirected_fd(full);
	operator = get_redirect_operator(full);
	target_file = get_target_file(full, filename, ft_strlen(operator));

	// printf("full ( %s )\nfilename ( %s )\n", full, filename);
	// printf("\tfd\t(%d)\n", file_fd);
	// printf("\toper\t( %s )\n", operator);
	// printf("\ttarget\t( %s )\n\n", target_file);


	check_operator_errors(file_fd, target_file, operator);

	if (check_filename_fd(target_file))
		target_fd = ft_atoi(target_file);
	else
		target_fd = open_check(target_file, REDIROVER);

	if ((ft_strequ((const char *)operator, "&>"))
		|| (ft_strequ((const char *)operator, ">&")))
	{
		dup2_check2(target_fd, 1);
		dup2_check2(1, 2);
	}
	else if (ft_strequ((const char *)operator, ">&-"))
	{
		// close_fd(file_fd);
		close(file_fd);
	}

	ft_strdel(&operator);
	ft_strdel(&target_file);
}


// int main(void)
// {
// 	// check_file_aggregations("1>&filename", NULL);
// 	// check_file_aggregations(">&filename", NULL);
// 	// check_file_aggregations("1>&", "sep_filename");
// 	// check_file_aggregations("2>&", "sep_filename");
// 	// check_file_aggregations(">&", "sep_filename");
// 	// check_file_aggregations(">&filename", NULL);
// 	// check_file_aggregations("&>", "sep_filename");
// 	// check_file_aggregations("&>", NULL);
// 	// check_file_aggregations(">&-", "sep_filename");
// 	// check_file_aggregations(">&-", NULL);
// 	// check_file_aggregations("|&", "sep_filename");
// 	// check_file_aggregations("3>&", NULL);

// 	check_bad_fd(0, "file");
// 	check_bad_fd(1, "file");
// 	check_bad_fd(2, "file");
// 	check_bad_fd(3, "file");
// 	check_bad_fd(4, "file");
// 	check_bad_fd(7, "file");
// 	check_bad_fd(9, "file");
// }


