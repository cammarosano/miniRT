/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:57:58 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:36:21 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	get_size(unsigned long int n, unsigned int radix)
{
	int	digits;

	digits = 1;
	while (n >= radix)
	{
		n /= radix;
		digits++;
	}
	return (digits);
}

/*
** Converts positive integer "nbr" to string in any valid base (which is not
** checked and is assumed to be valid). Returned string is a freeable pointer.
*/

char	*ft_utoa_base(unsigned long long nbr, char *base)
{
	char			*str;
	int				size;
	unsigned int	radix;

	radix = ft_strlen(base);
	size = get_size(nbr, radix);
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	while (nbr >= radix)
	{
		str[size--] = base[nbr % radix];
		nbr /= radix;
	}
	str[size] = base[nbr % radix];
	return (str);
}
