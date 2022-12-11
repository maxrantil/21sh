/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/09 16:18:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	main(void)
{
	t_node	*root;
	t_shell	sh;
	t_term	t;
	char	*line;

	root = NULL;
	init(&sh, &t);
	while (ft_input_cycle(&t))
	{
		sh.cl = lexer(&t);
		write(1, "\n", 1);
		if (sh.cl)
		{
			line = sh.cl;
			root = parse_line(&line);
			if (root)
				exec_tree(root, &sh);
		}
		ft_memdel((void **)&sh.cl);
		free_mem(root, &sh, 1);
		ft_restart_cycle(&t);
	}
	free_mem(root, &sh, 3);
	ft_history_write_to_file(&t);
	exit(1);
}
