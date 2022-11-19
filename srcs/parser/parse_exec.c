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

void 	add_to_array(char ***array, char *str)
{
	int 	i;
	char	**new_array;

	i = 0;
	if (*array == NULL)
	{
		*array = (char **)malloc(sizeof(char *) * 2);
		(*array)[0] = ft_strdup(str);
		(*array)[1] = NULL;
		return ;
	}
	while ((*array)[i])
		i++;
	new_array = (char **)malloc(sizeof(char *) * (i + 2));
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
	// size_t	argc;
	t_node	*node;

	node = node_create(EXEC, NULL, NULL);
	node = parse_redirection(node, ptr_to_line);
	// argc = 0;
	while (**ptr_to_line && !peek(ptr_to_line, "|&;"))
	{
		type = token_get(ptr_to_line, &token, &end_q);
		if (type == 'a')
			// node->arg[argc++] = ft_strsub(token, 0, (size_t)(end_q - token)); //make args a douple pointer instead?
			add_to_array(&node->arg, ft_strsub(token, 0, (size_t)(end_q - token)));
		else if (type == 0)
			break ;
		else
		{
			ft_printf("syntax error near unexpected token `%c'\n", type);
			exit(1);
		}
		node = parse_redirection(node, ptr_to_line);
	}
	// if (node)
		// node->arg[argc] = NULL;
	return (node);
}
