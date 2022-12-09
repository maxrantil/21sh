/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_banner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:16:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/30 10:25:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/* static int    banner_padding(size_t str_len)
{
    struct winsize    arg;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &arg);
    return ((arg.ws_col - str_len) >> 1);
} */

void print_banner(void)
{
	ft_run_capability("cl");
	/* banner_padding(); */
	ft_putstr("\033[2J");
	ft_putstr("\033[H");
	ft_printf("\n{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**\n");
	ft_printf("            {blu}- {yel}2{gre}1{red}s{blu}h {yel}-\n");
	ft_printf("   {yel}made {blu}by {gre}rvuorenl {red}and {yel}mrantil{blu}.");
	ft_printf("\n{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{nor}\n\n");
}
