/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 14:47:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*ft_trim_line(t_term *t)
{
	char	*new;

	new = ft_strtrim(t->inp);
	new = check_heredoc(t, new);
	write(1, "\n", 1);
	return (new);
}

int	main(void)
{
	t_node	*root;
	t_shell	sh;
	t_term	t;
	t_line	l;

	root = NULL;
	init(&sh, &t);
	while (ft_input_cycle(&t))
	{
		sh.cl = ft_trim_line(&t);
		if (sh.cl)
		{
			l.line = sh.cl;
			root = parse_line(&l, &l.line);
			if (root)
				if (!exec_tree(root, &sh))
					break ;
		}
		free_mem(root, &sh, 1);
	}
	free_mem(root, &sh, 3);
	exit(0);
}
