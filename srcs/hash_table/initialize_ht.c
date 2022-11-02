/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_ht.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/02 10:22:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * It takes a hash table and a pointer to a builtin, and inserts the builtin into the hash table
 */
static char	*ht_insert(t_builtin **ht, t_builtin *p)
{
	size_t index;
	
	if (!p)
		return (NULL);
	index = hash_function(p->program);
	p->next = ht[index];
	ht[index] = p;
	return (ht[index]->program);
}

static void	init_ht_struct(t_builtin **ht, char *str, int (*f)(t_msh *msh))
{
	t_builtin	*new;

	new = (t_builtin *)ft_memalloc(sizeof(t_builtin));
	new->program = str;
	new->function = f;
	new->next = NULL;
	ht_insert(ht, new);
}

static void	init_ht(t_builtin **ht)
{
	int	i;

	i =	0;
	while (i < HASH_SIZE)
		ht[i++] = NULL;
}
	
void initialize_ht(t_builtin **ht)
{
	init_ht(ht);
	init_ht_struct(ht, "cd", &msh_cd);
	init_ht_struct(ht, "echo", &msh_echo);
	init_ht_struct(ht, "env", &msh_env);
	init_ht_struct(ht, "exit", &msh_exit);
	init_ht_struct(ht, "setenv", &msh_setenv);
	init_ht_struct(ht, "unsetenv", &msh_unsetenv);
}
