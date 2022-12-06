/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:10:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/06 16:59:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	hash_print(t_hash **ht)
{
	t_hash	*tmp;
	int		i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (ht[i])
		{
			ft_printf("hits    command\n");
			break ;
		}
		i++;
	}
	i = 0;
	while (i < HASH_SIZE)
	{
		/* if (!ht[i])
			ft_printf("ht[%d] = NULL", i);
		else */
		if (ht[i])
		{
			// ft_printf("ht[%d] = ", i);
			tmp = ht[i];
			while (tmp)
			{
				ft_printf("%4d	%s\n",0, tmp->program);
				tmp = tmp->next;
			}
			ft_printf("\n");
		}
		i++;
	}
}
