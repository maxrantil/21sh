/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:13 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:35:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node	*node_create(int type, t_node *left, t_node *right)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	// ft_memset(node->arg, 0, 100);
	node->arg = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}
