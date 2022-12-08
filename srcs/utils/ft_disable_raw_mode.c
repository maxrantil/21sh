/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disable_raw_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:59:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 16:43:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_disable_raw_mode(t_shell *sh)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->orig_termios);
}
