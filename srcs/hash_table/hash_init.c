/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 17:31:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It takes a hash table and a pointer to a builtin, and inserts the builtin into the hash table
 */
static char	*ht_insert(t_hash **ht, t_hash *p)
{
	size_t index;

	if (!p)
		return (NULL);
	index = hash_function(p->program);
	p->next = ht[index];
	ht[index] = p;
	return (ht[index]->program);
}

static void	init_ht_struct(t_hash ***ht, char *str, int (*f)(t_node *n, t_shell *sh))
{
	t_hash	*new;

	new = (t_hash *)ft_memalloc(sizeof(t_hash));
	new->program = str;
	new->function = f;
	new->next = NULL;
	ht_insert(*ht, new);
}

static void	init_ht(t_hash ***ht)
{
	int	i;

	*ht = (t_hash **)malloc(sizeof(t_hash *) * (HASH_SIZE + 1)); //be sure to free this, not done now
	i =	0;
	while (i < HASH_SIZE)
		(*ht)[i++] = NULL;
}

void hash_init(t_hash ***ht)
{
	init_ht(ht);
	init_ht_struct(ht, "cd", &msh_cd);
	init_ht_struct(ht, "echo", &msh_echo);
	init_ht_struct(ht, "env", &msh_env);
	init_ht_struct(ht, "exit", &msh_exit);
	init_ht_struct(ht, "setenv", &msh_setenv);
	init_ht_struct(ht, "unsetenv", &msh_unsetenv);
}
