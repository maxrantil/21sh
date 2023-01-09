/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:55:32 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/09 12:57:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
	TEST: getcwd failure
*/
char	*ft_get_file(char *str)
{
	char	cwd[MAX_PATH];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, str));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, str));
}
