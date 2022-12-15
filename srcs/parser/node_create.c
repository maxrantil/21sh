/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:13 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 12:11:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*node_create(int type, t_node *left, t_node *right)
{
	t_node	*n;

	n = (t_node *)malloc(sizeof(t_node));
	n->arg = NULL;
	n->type = type;
	n->left = left;
	n->right = right;
	return (n);
}
