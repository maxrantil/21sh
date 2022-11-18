/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 17:08:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	print_echo(t_node *node, t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	(void)msh;
	arrlen = ft_arrlen((void **)node->arg);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		while (node->arg[i][j] != '\0')
			write(1, &node->arg[i][j++], 1);
		i++;
		if (node->arg[i])
			ft_putchar(' ');
	}
}

int	msh_echo(t_node *node, t_msh *msh)
{
	print_echo(node, msh);
	ft_putchar('\n');
	return (1);
}
