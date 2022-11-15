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

int	msh_setenv(t_node *node, t_msh *msh)
{
	size_t	i;

	i = 1;
	while (node->arg[i])
	{
		if (strchr(node->arg[i], '=') \
		&& (ft_isalpha(node->arg[i][0]) || node->arg[i][0] == '_'))
			setenv_loop(msh, node->arg[i], 0);
		else
			print_error(node->arg[i], 6);
		i++;
	}
	return (1);
}
