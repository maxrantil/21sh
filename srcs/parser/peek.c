/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:03:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:31:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	peek(char **ptr_to_line, char *toks)
{
	char *scan;

	scan = *ptr_to_line;
	scan = ft_skip_whitespaces(scan);
	*ptr_to_line = scan;
	return (*scan && ft_strchr(toks, *scan));
}
