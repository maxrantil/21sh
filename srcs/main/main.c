/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/09 15:01:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	main()
{
	t_node	*root;
	t_shell	sh;
	t_term	t;
	int		status;

	root = NULL;
	init(&sh, &t);
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
			status = exec_tree(root, &sh);
		}
		ft_memdel((void **)&sh.cl);
		free_mem(root, &sh, 1);
		ft_restart_cycle(&t);
	}
	free_mem(root, &sh, 3);
	ft_history_write_to_file(&t);
	exit(20);
}
