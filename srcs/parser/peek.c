/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:03:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 14:04:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	peek(char **ptr_to_str, char *toks)
{
	char *scan;

	scan = *ptr_to_str;
	while (*scan && ft_isspace((const char *)scan))
		scan++;
	*ptr_to_str = scan;
	return (*scan && ft_strchr(toks, *scan));
}
