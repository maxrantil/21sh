/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:28:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/15 11:40:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	print_exec(t_node *root)
{
	size_t	len;

	len = ft_arrlen((void **)root->arg);
	ft_printf("exec ");
	if (len > 2)
		ft_printf("[%s] [1]%s [2]%s [3]%s\n", root->arg[0], \
		root->arg[1], root->arg[2], root->arg[3]);
	else if (len == 2)
		ft_printf("[%s] %s\n", root->arg[0], root->arg[1]);
	else
		ft_printf("[%s]\n", root->arg[0]);
}

static void	check_type(t_node *root)
{
	if (root->type == EXEC && root->arg)
		print_exec(root);
	else if (root->type == PIPE)
		ft_printf("[|]");
	else if (root->type == REDIROVER && root->arg)
		ft_printf("> [%s] [%s]\n", root->arg[0], root->arg[1]);
	else if (root->type == REDIRAPP && root->arg)
		ft_printf(">> [%s] [%s]\n", root->arg[0], root->arg[1]);
	else if (root->type == REDIRIN && root->arg)
		ft_printf("< [%s] [%s]\n", root->arg[0], root->arg[1]);
	else if (root->type == AMP)
		ft_printf("[&]");
	else if (root->type == SEMI)
		ft_printf("[;]");
	else if (root->type == FILEAGG && root->arg)
		ft_printf(">& [%s] [%s]\n", root->arg[0], root->arg[1]);
}

void	rec_print_tree(t_node *root, int lvl)
{
	int	i;

	if (root == NULL)
		return ;
	lvl += COUNT;
	rec_print_tree(root->right, lvl);
	ft_printf("\n");
	i = COUNT;
	while (i++ < lvl)
		ft_printf(" ");
	check_type(root);
	rec_print_tree(root->left, lvl);
}

void	tree_print(t_node *root)
{
	write(1, "\n------------------ TREE PRINT ------------------\n", 66);
	if (root)
		rec_print_tree(root, 0);
	write(1, "\n------------------ TREE PRINT ------------------\n\n", 67);
}
