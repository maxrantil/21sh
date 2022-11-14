/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 13:47:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	key = ft_strnew(ft_strlen(key_value));
	if (ft_strchr(key_value, '='))
	{
		while (key_value[i] != '=')
			i++;
		ft_strncpy(key, key_value, i);
	}
	else
		ft_strcpy(key, key_value);
	key = ft_strupdate(key, "=");
	return (key);
}
