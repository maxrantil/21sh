/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:42:50 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 11:42:56 by rvuorenl         ###   ########.fr       */
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
