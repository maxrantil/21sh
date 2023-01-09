/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_add_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:39:52 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/06 14:42:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	add_to_capped_history(t_term *t, char *command)
{
	char	**temp;
	int		i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (MAX_HISTORY + 1));
	if (!temp)
		exit(1);
	while (t->history[i + 1])
	{
		temp[i] = ft_strdup(t->history[i + 1]);
		i++;
	}
	temp[i] = ft_strdup(command);
	i++;
	temp[i] = NULL;
	ft_arrfree((void ***)&t->history, ft_arrlen((void **)t->history));
	t->history = temp;
}

/*
	memmove possible
*/

static void	increase_history_size(t_term *t)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (t->history_size + 2));
	if (temp)
	{
		i = -1;
		while (t->history[++i])
			temp[i] = ft_strdup(t->history[i]);
		temp[i] = NULL;
		ft_arrfree((void ***)&t->history, ft_arrlen((void **)t->history));
		t->history = temp;
	}
	else
	{
		ft_putendl_fd("21sh: malloc error, increase_history_size()", 2);
		exit(1);
	}
}

void	ft_history_add_command(t_term *t, char *command)
{
	int    i;

	if (t->history_size <= MAX_HISTORY)
	{
		i = 0;
		while (command[i] && ft_isspace(&command[i]))
			i++;
		if (!command[i])
			return ;
		increase_history_size(t);
		t->history[t->history_size] = ft_strdup(command);
		t->history_size++;
		t->history[t->history_size] = NULL;
	}
	else
		add_to_capped_history(t, command);
}
