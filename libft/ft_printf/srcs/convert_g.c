/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_g.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:06:31 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:35:33 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static char	*sci_notation(double nbr, int exp, int significant, int flags)
{
	char	*float_str;
	char	*expon_str;
	char	*dst;

	float_str = float_to_str(nbr, significant - 1, flags);
	if (significant > 1 && !(flags & FLAG_HASH))
	{
		trim_from_right(float_str, '0');
		trim_from_right(float_str, '.');
	}
	expon_str = get_expon_str(exp);
	dst = ft_strjoin(float_str, expon_str);
	free(float_str);
	free(expon_str);
	return (dst);
}

static char	*standard_notation(double nbr, int precision, int flags)
{
	char	*str;

	str = float_to_str(nbr, precision, flags);
	if (precision > 0 && !(flags & FLAG_HASH))
	{
		trim_from_right(str, '0');
		trim_from_right(str, '.');
	}
	return (str);
}

static int	precision_to_signif_dig(int precision)
{
	int		significant;

	if (precision < 0)
		significant = 6;
	else if (precision == 0)
		significant = 1;
	else
		significant = precision;
	return (significant);
}

char	*float_to_str_signif(double nbr, int precision, int flags)
{
	int		exp;
	double	nbr_e;
	char	*str;
	int		significant;

	significant = precision_to_signif_dig(precision);
	nbr_e = nbr;
	exp = 0;
	while (nbr_e != 0 && nbr_e > -1 && nbr_e < 1)
	{
		nbr_e *= 10;
		exp--;
	}
	while (nbr_e <= -10 || nbr_e >= 10 || test_rounding(nbr_e, significant - 1))
	{
		nbr_e /= 10;
		exp++;
	}
	if (exp < -4 || exp >= significant)
		str = sci_notation(nbr_e, exp, significant, flags);
	else
		str = standard_notation(nbr, significant - 1 - exp, flags);
	return (str);
}
