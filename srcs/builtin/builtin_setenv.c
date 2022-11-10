/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 15:46:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_setenv(t_msh *msh)
{
	size_t	i;

	i = 1;
	while (msh->args[i])
	{
		if (strchr(msh->args[i], '=') \
		&& (ft_isalpha(msh->args[i][0]) || msh->args[i][0] == '_'))
			loop_setenv(msh, msh->args[i], 0);
		else
			print_error(msh->args[i], 6);
		i++;
	}
	return (1);
}
