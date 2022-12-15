/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:27:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 13:27:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*error_redir(t_node *n, char **ptr_to_line)
{
	ft_putstr_fd("21sh: (redir) syntax error near unexpected tok `", 2);
	if (**ptr_to_line)
		ft_putchar_fd(**ptr_to_line, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	tree_free(n);
	return (NULL);
}
