/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:19:48 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/02 10:20:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
**	It takes a string and returns an integer
**	@return The hash value of the program name.
*/
size_t hash_function(char *program)
{
	size_t	hash;
	size_t 	c;

	hash = 0;
	while ((c = (size_t)*program++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return (hash % HASH_SIZE);
}
