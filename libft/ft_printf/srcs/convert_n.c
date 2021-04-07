/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 07:05:01 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:17:59 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Handles the %n conversion.
** The number of BYTES (not characters) written so far is stored in the integer
** pointed by the argument.
** Returns -1 if error, 0 otherwise (as no character gets written to stdout for
** this conversion).
*/

int	convert_n(int length, va_list args, int counter)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (-1);
	if (length == 0)
		*(int *)ptr = counter;
	else if (length == len_hh)
		*(signed char *)ptr = counter;
	else if (length == len_h)
		*(short *)ptr = counter;
	else if (length == len_l)
		*(long *)ptr = counter;
	else
		*(long long *)ptr = counter;
	return (0);
}
