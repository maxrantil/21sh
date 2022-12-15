/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ht_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 12:51:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It takes a hash table and a pointer to a builtin, and inserts the builtin
 * into the hash table
 */
static void	ht_insert(t_shell *sh, t_hash *new)
{
	size_t	index;

	index = hash_function(new->program);
	new->next = sh->ht[index];
	sh->ht[index] = new;
}

void	init_ht_struct(t_shell *sh, char *str)
{
	t_hash	*new;

	new = (t_hash *)malloc(sizeof(t_hash));
	if (!new)
	{
		ft_putstr_fd("malloc fail on init_ht_struct\n", 2);
		return ;
	}
	new->program = ft_strdup(str);
	new->hits = 0;
	new->next = NULL;
	ht_insert(sh, new);
}
