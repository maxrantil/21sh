/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/02 18:21:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_disable_raw_mode(t_term *t)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->orig_termios);
}

static int ft_getent(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		status;

	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		ft_putendl_fd("could not get the TERM env", 2);
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status < 0)
	{
		ft_putendl_fd("could not access the termcap data base", 2);
		exit(1);
	}
	else if (status == 0)
	{
		ft_putendl_fd("could not find the termtype", 2);
		exit(1);
	}
	return (status);
}

static void	get_terminal_name(char **terminal_name)
{
	*terminal_name = ttyname(1);
}

static void	reset_fds(char *terminal_name)
{
	/* int	fd0;
	int	fd1;
	int	fd2; */

	close(0);
	/* fd0 =  */open(terminal_name, O_RDWR);
	close(1);
	/* fd1 =  */open(terminal_name, O_RDWR);
	close(2);
	/* fd2 =  */open(terminal_name, O_RDWR);
}

int	main()
{
	t_node	*root;
	t_shell	sh;
	t_term	t;
	t_hash	**ht;
	int status;

	get_terminal_name(&(sh.terminal_name));
	ht = NULL;
	root = NULL;
	ft_getent();
	init(&sh, &t, &ht);
	status = 21;
	while (status)
	{
		status = ft_input_cycle(&t);
		if (!status)
			break ;
		sh.cl = lexer(&t);
		write(1, "\n", 1);
		if (sh.cl && status > 0)
		{
			char *p = sh.cl;
			root = parse_line(&p);
			status = exec_tree(root, &sh, ht);
		}
		ft_memdel((void **)&sh.cl);
		free_mem(root, &sh, ht, 1);
		reset_fds(sh.terminal_name);
		ft_restart_cycle(&t);
	}
	free_mem(root, &sh, ht, 3);
	ft_history_write_to_file(&t);
	ft_disable_raw_mode(&t);
	exit(20);
}
