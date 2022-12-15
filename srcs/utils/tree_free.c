/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:40:31 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 11:48:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * tree_free - Recursively free memory allocated for a binary tree
 *
 * @n: Pointer to the root node of the tree
 */
void	tree_free(t_node *n)
{
	if (!n)
		return ;
	if (n->left)
		tree_free(n->left);
	if (n->right)
		tree_free(n->right);
	n->left = NULL;
	n->right = NULL;
	ft_arrfree((void ***)&n->arg, ft_arrlen((void **)n->arg));
	free(n);
	n = NULL;
}
