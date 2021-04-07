/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:09:51 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 14:00:17 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	get_size(long long n)
{
	int	digits;

	digits = 1;
	if (n < 0)
		digits = 2;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static int	we_love_ternaries(int test, int r_true, int r_false)
{
	if (test)
		return (r_true);
	return (r_false);
}

char	*ft_lltoa(long long n)
{
	char	*str;
	int		size;
	int		sign;

	sign = we_love_ternaries(n < 0, -1, 1);
	size = get_size(n);
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	while (n >= 10 || n <= -10)
	{
		str[size--] = (n % 10) * sign + '0';
		n /= 10;
	}
	str[size--] = (n % 10) * sign + '0';
	if (sign == -1)
		str[size] = '-';
	return (str);
}
