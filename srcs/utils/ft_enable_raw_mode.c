/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enable_raw_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:50:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 12:57:35 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	If optional_actions is TCSAFLUSH, the change shall occur after all output
**	written to fildes is transmitted, and all input so far received but not
**	read shall be discarded before the change is made.
*/
void	ft_enable_raw_mode(t_shell *sh)
{
	if (tcgetattr(STDIN_FILENO, &sh->orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	sh->raw = sh->orig_termios;
	sh->raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	sh->raw.c_iflag &= ~(IXON | BRKINT);
	sh->raw.c_cc[VMIN] = 1;
	sh->raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
}
