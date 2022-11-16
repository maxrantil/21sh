/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/16 12:05:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	If optional_actions is TCSAFLUSH, the change shall occur after all output
**	written to fildes is transmitted, and all input so far received but not
**	read shall be discarded before the change is made.
*/
static struct termios	ft_init_raw(void)
{
	struct termios	orig_termios;
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw = orig_termios;
	raw.c_lflag &= ~(size_t)(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(size_t)(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	ft_run_capability("ti");
	ft_run_capability("cl");
	return (orig_termios);
}

static void	ft_disable_raw_mode(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
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
	struct termios	orig_termios;
	t_msh			msh;
	t_term			t;
	t_node			*root;
	t_builtin		*ht[HASH_SIZE];
	char			*line;

	ft_getent();
	orig_termios = ft_init_raw();
	init(&msh, &t, ht);
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
				status = exec_tree(root, &msh, ht);
				// tree_free(root);
			}
		}
		ft_restart_cycle(&t);
		free_mem(&msh, ht, 1);
	}
	free_mem(&msh, ht, 2);
	ft_history_write_to_file(&t);
	ft_disable_raw_mode(orig_termios);
	exit(0);
}
