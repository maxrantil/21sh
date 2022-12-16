/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_env_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:21:45 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/16 13:26:03 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*get_full_env_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ((ft_isalnum(var[i])) || var[i] == '_'))
		i++;
	return (ft_strsub((const char *)var, 0, (size_t)i));
}
