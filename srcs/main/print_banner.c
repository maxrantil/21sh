/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_banner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:16:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 13:27:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_banner(void)
{
	ft_run_capability("cl");
	ft_putstr("\033[2J");
	ft_putstr("\033[H");
	ft_printf("\n      {red}*{yel}*{blu}*{gre}*\n");
	ft_printf("    {blu}- {yel}2{gre}1{red}s{blu}h {yel}-\n");
	ft_printf("  {blu}by {gre}rvuorenl\n");
	ft_printf(" {red}and  {yel}mrantil{blu}.\n");
	ft_printf("{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{nor}\
	\n\n");
}
