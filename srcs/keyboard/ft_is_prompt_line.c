/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prompt_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:40:13 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 10:40:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns a pointer to the beginning of the line if the line is a prompt
 * line, otherwise it returns NULL
 *
 * @param t the terminal structure
 * @param row the row of the cursor
 *
 * @return The address of the first character of the line.
 */
char	*ft_is_prompt_line(t_term *t, ssize_t row)
{
	if (!row || t->nl_addr[row][-1] == '\n')
		return (t->nl_addr[row]);
	return (NULL);
}
