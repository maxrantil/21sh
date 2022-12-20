/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_file_get.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 14:51:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the path to the history file
 *
 * @return The path to the history file.
 */
char	*ft_history_file_get(void)
{
	char	cwd[1024];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, "/.ft_21sh_history"));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, "/.ft_21sh_history"));
}
