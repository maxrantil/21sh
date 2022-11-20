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

static void	print_echo(t_node *n, t_shell *sh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	(void)sh;
	arrlen = ft_arrlen((void **)n->arg);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		while (n->arg[i][j] != '\0')
			write(1, &n->arg[i][j++], 1);
		i++;
		if (n->arg[i])
			ft_putchar(' ');
	}
}

int	msh_echo(t_node *n, t_shell *sh)
{
	print_echo(n, sh);
	ft_putchar('\n');
	return (1);
}
