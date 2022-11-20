/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 16:57:43 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	msh_setenv(t_node *n, t_shell *sh)
{
	size_t	i;

	i = 1;
	while (n->arg[i])
	{
		if (strchr(n->arg[i], '=') \
		&& (ft_isalpha(n->arg[i][0]) || n->arg[i][0] == '_'))
			setenv_loop(sh, n->arg[i], 0);
		else
			error_print(n->arg[i], 6);
		i++;
	}
	return (1);
}
