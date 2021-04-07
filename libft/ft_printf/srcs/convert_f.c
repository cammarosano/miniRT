/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:41:35 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 14:58:51 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static char	*append_minus(char *src)
{
	char	*dst;

	dst = ft_strjoin("-", src);
	free(src);
	return (dst);
}

/*
** left and right must be freeable strings.
*/

static char	*join_decimal_sep(char *left, char *right)
{
	char	*str;
	char	*temp;
	char	*dec_sep;

	dec_sep = localeconv()->decimal_point;
	temp = ft_strjoin(left, dec_sep);
	str = ft_strjoin(temp, right);
	free(left);
	free(right);
	free(temp);
	return (str);
}

static char	*append_decimal_sep(char *left, int flags)
{
	char	*dst;
	char	*dec_sep;

	if (!(flags & FLAG_HASH))
		return (left);
	dec_sep = localeconv()->decimal_point;
	dst = ft_strjoin(left, dec_sep);
	free(left);
	return (dst);
}

static double	pow_float(double nbr_fractional, int precision)
{
	while (precision--)
		nbr_fractional *= 10;
	return (nbr_fractional);
}

/*
** Converts each of the integer and fractional parts of (double) nbr to an
** unsigned long long int, which are converted to strings and joined by the
** apropriate decimal separator (depending on the LOCALE).
** Returns a freeable string, or NULL pointer if malloc error.
** Obs: Malloc errors ARE being handled. This relies on the property of
** ft_strjoin returning NULL if any of the source strings is NULL.
*/

char	*float_to_str(double nbr, int precision, int flags)
{
	unsigned long long	integer;
	unsigned long long	fractional;
	char				*left;
	char				*right;
	int					sign_neg;

	sign_neg = resolve_sign_neg(&nbr);
	if (precision < 0)
		precision = 6;
	if (!check_ull_overflow(nbr, precision))
		return (NULL);
	nbr += (double)5 / ten_power(precision + 1);
	integer = (unsigned long long)nbr;
	fractional = (unsigned long long)pow_float(nbr - integer, precision);
	left = ft_utoa_base(integer, "0123456789");
	if (sign_neg)
		left = append_minus(left);
	if (precision == 0)
		return (append_decimal_sep(left, flags));
	right = ft_utoa_base(fractional, "0123456789");
	if (right)
		right = adjust_precision(right, precision);
	return (join_decimal_sep(left, right));
}
