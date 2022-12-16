/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 14:48:14 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_open_stdout(void)
{
	struct stat	buf;
	int			ret;

	ret = fstat(1, &buf);
	if (ret == -1)
		ft_putstr_fd("21sh: echo: write error: Bad file descriptor\n", 2);
	return (ret);
}

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

int	sh_echo(t_node *n, t_shell *sh)
{
	if (check_open_stdout() != -1)
	{
		print_echo(n, sh);
		ft_putchar('\n');
		return (1);
	}
	return (-1);
}
