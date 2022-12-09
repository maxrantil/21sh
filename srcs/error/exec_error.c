/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:57:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/09 11:59:54 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*exec_error(t_node *n, int type)
{
	ft_putstr_fd("exec syntax error near unexpected tok `", 2);
	if (type == '#')
		ft_putstr_fd(">>", 2);
	else
		ft_putchar_fd(type, 2);
	ft_putendl_fd("'", 2);
	tree_free(n);
	return (NULL);
}
