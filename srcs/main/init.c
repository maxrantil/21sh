/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 15:20:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_getent(void)
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

void	init(t_shell *sh, t_term *t)
{
	ft_getent();
	ft_enable_raw_mode(sh);
	get_terminal_name(&(sh->terminal_name));
	print_banner();
	ft_init_term(t);
	hash_init(sh);
	sh->paths = NULL;
	sh->env = NULL;
	sh->cl = NULL;
	sh->env = get_env(sh->env);
	sh->temp_env = NULL;
	vec_new(&sh->v_tmp_env, 0, MAX_PATHLEN);
	ft_printf("{yel}${gre}>{nor} ");
}
