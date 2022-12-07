/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:10:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/07 13:15:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	hash_print(t_hash **ht)
{
	t_hash	*tmp;
	int		i;
	// int		j;

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
	if (i == HASH_SIZE)
	{
		ft_putstr_fd("21sh: hash table empty", 2);
		return ;
	}
	i = 0;
	while (i < HASH_SIZE)
	{
		if (ht[i] != NULL)
		{
			tmp = ht[i];
			while (tmp != NULL)
			{
				ft_printf("%d	%s\n", tmp->hits, tmp->program);
				tmp = tmp->next;
			}
		}
		i++;
	}
}
