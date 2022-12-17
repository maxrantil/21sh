/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.SIZE_MAX == ULONG_MAXc                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 11:09:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_term	*g_t;

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

static void	get_term_name(char **term_name)
{
	*term_name = ttyname(1);
}

void	init(t_shell *sh, t_term *t)
{
	ft_getent();
	ft_enable_raw_mode(sh);
	get_term_name(&(sh->term_name));
	g_t = t;
	print_banner();
	ft_init_term(t);
	hash_init(sh);
	sh->paths = NULL;
	sh->env = NULL;
	sh->cl = NULL;
	sh->env = get_env(sh->env);
	sh->temp_env = NULL;
	vec_new(&sh->v_tmp_env, 0, BUFFSIZE);
	ft_printf("{yel}${gre}>{nor} ");
}
