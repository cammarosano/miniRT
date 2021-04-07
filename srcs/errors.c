/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:07:38 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:18:36 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sc_err(int line_num, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("Scene description file", 2);
	if (line_num)
	{
		ft_putstr_fd(", line ", 2);
		ft_putnbr_fd(line_num, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (0);
}

int	syscall_err(char *function_name)
{
	ft_putendl_fd("Error", 2);
	perror(function_name);
	return (0);
}

void	sc_warning(int line_num, char *msg)
{
	ft_putstr_fd("Warning: scene description file", 2);
	if (line_num)
	{
		ft_putstr_fd(", line ", 2);
		ft_putnbr_fd(line_num, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}
