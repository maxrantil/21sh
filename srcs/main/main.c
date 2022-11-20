/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 17:32:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_disable_raw_mode(t_term *t)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->orig_termios);
	ft_run_capability("te");
}

static int ft_getent(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		status;

	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		ft_printf("could not get the TERM env\n");
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status < 0)
	{
		ft_printf("could not access the termcap data base\n");
		exit(1);
	}
	else if (status == 0)
	{
		ft_printf("could not find the termtype\n");
		exit(1);
	}
	return (status);
}

int last_step(t_shell *sh, t_hash **ht, char *line)
{
	t_node	*root;
	int		status;

	status = 1;
	root = parse_line(&line);
	if (root)
	{
		// tree_print(root);
		status = exec_tree(root, sh, ht);
		tree_free(root);
	}
	return (status);
}

int	main(int argc, char **argv)
{
	t_shell	sh;
	t_term	t;
	t_hash	**ht;
	char	*line;
	int status = 1;

	ht = NULL;
	ft_getent();
	init(&sh, &t, &ht, argc, argv);
	while (status)
	{
		if (!ft_input_cycle(&t))
			break ;
		if (t.bytes)
			line = lexer(t.inp);
		write(1, "\n", 1);
		if (line)
		{
			//strip_quotes(&line);				//wrote place but this is only for testing, invalid read in this function according to Valgrind
			status = last_step(&sh, ht, line);
		}
		ft_restart_cycle(&t);
		free_mem(&sh, ht, 1);
		ft_strdel(&line);
	}
	free_mem(&sh, ht, 2);
	ft_history_write_to_file(&t);
	ft_disable_raw_mode(&t);
	exit(20);
}
