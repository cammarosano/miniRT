/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:11:44 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:34:21 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	message_size(void)
{
	char	*llu_limit;

	llu_limit = ft_utoa_base(ULLONG_MAX, "0123456789");
	if (!llu_limit)
		return (0);
	ft_putstr_fd("\n(error: ft_printf does not support floating point \
conversion of numbers with modulo greater than ", 2);
	ft_putstr_fd(llu_limit, 2);
	ft_putstr_fd(")\n", 2);
	return (0);
}

static int	message_precision(void)
{
	ft_putstr_fd("\n(error: could not convert floating point number with the \
given precision)\n", 2);
	return (0);
}

int	check_ull_overflow(double nbr, int precision)
{
	if (nbr > ULLONG_MAX)
		return (message_size());
	nbr += (double)5 / ten_power(precision + 1);
	if (nbr > ULLONG_MAX)
		return (message_size());
	nbr -= (unsigned long long)nbr;
	while (precision--)
		nbr *= 10;
	if (nbr > ULLONG_MAX)
		return (message_precision());
	return (1);
}
