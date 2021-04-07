/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:06:31 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:05:08 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

unsigned long long	ten_power(unsigned int exponent)
{
	unsigned long long	res;

	res = 1;
	while (exponent--)
		res *= 10;
	return (res);
}

int	test_rounding(double nbr, int precision)
{
	if (nbr < 0)
		nbr *= -1;
	if (precision < 0)
		precision = 6;
	nbr += (double)5 / ten_power(precision + 1);
	if (nbr >= 10)
		return (1);
	return (0);
}

char	*get_expon_str(int n)
{
	char	*str;
	int		sign;

	str = malloc(sizeof(*str) * 5);
	if (!str)
		return (NULL);
	sign = 1;
	if (n < 0)
		sign = -1;
	str[4] = '\0';
	str[3] = (n % 10) * sign + '0';
	n /= 10;
	str[2] = (n % 10) * sign + '0';
	if (sign == 1)
		str[1] = '+';
	else
		str[1] = '-';
	str[0] = 'e';
	return (str);
}

char	*float_to_str_sci(double nbr, int precision, int flags)
{
	int		exp;
	char	*float_str;
	char	*expon_str;
	char	*dst;

	exp = 0;
	while (nbr != 0 && nbr > -1 && nbr < 1)
	{
		nbr *= 10;
		exp--;
	}
	while (nbr <= -10 || nbr >= 10 || test_rounding(nbr, precision))
	{
		nbr /= 10;
		exp++;
	}
	float_str = float_to_str(nbr, precision, flags);
	expon_str = get_expon_str(exp);
	dst = ft_strjoin(float_str, expon_str);
	free(float_str);
	free(expon_str);
	return (dst);
}
