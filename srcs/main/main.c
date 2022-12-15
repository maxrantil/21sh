/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 10:09:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	main(void)
{
	t_node	*root;
	t_shell	sh;
	t_term	t;
	t_line	l;
	// char	*line;

	root = NULL;
	init(&sh, &t, &l);
	while (ft_input_cycle(&t))
	{
		sh.cl = lexer(&t);
		if (sh.cl)
		{
			l.line = sh.cl;
			root = parse_line(&l);
			if (root)
				if (!exec_tree(root, &sh))
					break ;
		}
		free_mem(root, &sh, 1);
		ft_restart_cycle(&t);
	}
	free_mem(root, &sh, 3);
	ft_history_write_to_file(&t);
	exit(0);
}
