/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/09 10:04:43 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term	*g_t;

int	sh_history(t_node *n, t_shell *sh)
{
	(void)sh;
	(void)n->arg;
	ft_history(g_t);
	return (1);
}
