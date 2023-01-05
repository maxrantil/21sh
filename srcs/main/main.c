/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/05 13:48:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*ft_trim_line(t_term *t)
{
	char	*new;

	write(1, "\n", 1);
	new = ft_strtrim(t->inp);
	if (t->heredoc && !t->delim)
	{
		ft_putstr_fd("21sh: syntax error near unexpected tok `newline'\n", 2);
		ft_strdel(&new);
		return (NULL);
	}
	new = check_heredoc(t, new);
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
		free_mem(root, &sh, LOOP);
	}
	free_mem(root, &sh, END);
	exit(0);
}
