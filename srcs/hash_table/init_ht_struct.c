/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ht_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/06 17:12:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It takes a hash table and a pointer to a builtin, and inserts the builtin into the hash table
 */
static char	*ht_insert(t_hash **ht, t_hash *new)
{
	size_t index;

	if (!new)
		return (NULL);
	index = hash_function(new->program);
	new->next = ht[index];
	ht[index] = new;
	return (ht[index]->program);
}

void	init_ht_struct(t_shell *sh, char *str/* , int (*f)(t_node *n, t_shell *sh) */)
{
	t_hash	*new;

	new = (t_hash *)ft_memalloc(sizeof(t_hash));
	new->program = str;
	// new->function = f;
	new->next = NULL;
	ht_insert(sh->ht, new);
}
