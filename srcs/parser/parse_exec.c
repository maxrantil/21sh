/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:25 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 12:33:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	**malloc_wrap(size_t size)
{
	char	**arr;

	arr = (char **)malloc(size);
	if (!arr)
	{
		ft_putendl_fd("error: malloc", 2);
		exit(1);
	}
	return (arr);
}

void 	add_to_array(char ***array, char *str)
{
	int 	i;
	char	**new_array;

	if (!str)
		return ;
	if (*array == NULL)
	{
		*array = malloc_wrap(sizeof(char *) * 2);
		(*array)[0] = str;
		(*array)[1] = NULL;
		return ;
	}
	i = 0;
	while ((*array)[i])
		i++;
	new_array = malloc_wrap(sizeof(char *) * (i + 2));
	i = 0;
	while ((*array)[i])
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	free(*array);
	*array = new_array;
}

t_node *parse_exec(char **ptr_to_line)
{
	char	*token;
	char	*end_q;
	int		type;
	t_node	*n;

	n = node_create(EXEC, NULL, NULL);
	n = parse_redirection(n, ptr_to_line);
	while (**ptr_to_line && n && !peek(ptr_to_line, "|&;"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		if (type == 'a')
			add_to_array(&n->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		else if (type == 0)
			break ;
		else
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			ft_putchar_fd(type, 2);
			ft_putendl_fd("'", 2);
			tree_free(n);
			return (NULL);
		}
		n = parse_redirection(n, ptr_to_line);
	}
	return (n);
}

