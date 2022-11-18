/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:12:07 by mrantil          ###   ########.fr       */
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

int	main(void)
{
	t_msh			msh;
	t_term			t;
	t_node			*root;
	t_builtin		**ht;
	char			*line;

	ht = NULL;
	ft_getent();
	init(&msh, &t, &ht);
	int status = 1;
	while (status)
	{
		if (!ft_input_cycle(&t))
			break ;
		/* msh.env = env_underscore(&msh); */
		if (t.bytes)
			line = ft_strdup(t.inp);
		// line = lexer(line);
		// ft_printf("Number of arguments: %d\n", count_arguments(t.inp));

		// ft_printf("line: %s\n", line);
		if (line)
		{
			root = parse_line(&line);
			if (root)
			{
				tree_print(root);
				status = exec_tree(root, &msh, ht); //no return here fix it
				tree_free(root);
			}
		}
		ft_restart_cycle(&t);
		free_mem(&msh, ht, 1);
	}
	free_mem(&msh, ht, 2);
	ft_history_write_to_file(&t);
	ft_disable_raw_mode(&t);
	exit(0);
}
