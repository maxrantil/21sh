/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 13:28:24 by mrantil          ###   ########.fr       */
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
		sh.cl = ft_heredoc(&t);
		if (sh.cl)
		{
			line = sh.cl;
			root = parse_line(&line);
			if (root) //do i need this?
				if (!exec_tree(root, &sh))
					break ;
		}
		free_mem(root, &sh, 1);
	}
	free_mem(root, &sh, 3);
	exit(0);
}
