/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/30 11:48:56 by mrantil          ###   ########.fr       */
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

int	main()
{
	t_node	*root;
	t_shell	sh;
	t_term	t;
	t_hash	**ht;
	int status = 1;

	ht = NULL;
	root = NULL;
	ft_getent();
	init(&sh, &t, &ht);
	while (status)
	{
		if (!ft_input_cycle(&t))
			break ;
		sh.cl = lexer(&t);
		write(1, "\n", 1);
		if (sh.cl)// && (!t.heredoc && *t.nl_addr[t.c_row]))
		{
			char *p = sh.cl;
			//strip_quotes(&sh.cl);				//wrote place but this is only for testing, invalid read in this function according to Valgrind
			root = parse_line(&p);
			status = exec_tree(root, &sh, ht);
		}
		ft_memdel((void **)&sh.cl);
		free_mem(root, &sh, ht, 1);
		ft_restart_cycle(&t);
	}
	free_mem(root, &sh, ht, 2);
	ft_history_write_to_file(&t);
	ft_disable_raw_mode(&t);
	exit(20);
}
