/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 14:09:09 by mrantil          ###   ########.fr       */
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

static int	exec_args(t_msh *msh, t_builtin **ht)
{
	t_builtin	*tmp;
	size_t		index;

	if (!msh->args[0])
		return (1);
	index = hash_function(msh->args[0]);
	tmp = ht[index];
	while (tmp)
	{
		if (ft_strcmp(msh->args[0], tmp->program) == 0)
			return (tmp->function(msh));
		tmp = tmp->next;
	}
	return (msh_launch(msh));
}

int	main(void)
{
	struct termios	orig_termios;
	t_msh			msh;
	t_term			t;
	t_builtin		*ht[HASH_SIZE];
	int				status;

	ft_getent();
	orig_termios = ft_init_raw();
	ft_init(&t);
	init(&msh);
	initialize_ht(ht);
	status = 1;
	while (status)
	{

		msh.cl = ft_input_cycle(&t);
		if (!msh.cl)
			break ;
		status = parser(&msh);
		if (status > 0)
		{
			status = exec_args(&msh, ht);
			msh.env = update_env_underscore(&msh);
		}
		free_mem(&msh, ht, 1);
	}
	free_mem(&msh, ht, 2);
	ft_history_write_to_file(&t);
	ft_disable_raw_mode(orig_termios);
	exit(0);
}
