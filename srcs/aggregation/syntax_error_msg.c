/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:44:46 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/12/13 13:59:51 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	syntax_error_msg(int exit_code)
{
	ft_putstr_fd("21sh: Syntax error!\n", 2);
	return (exit_code);
}
