/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aggregation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:04:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/11/29 09:46:05 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	check_filename_fd(char *filename)
{
	int	i;

	i = -1;
	while (filename[++i])
	{
		if (!ft_isdigit(filename[i]))
			return (0);
	}
	return (1);
}
