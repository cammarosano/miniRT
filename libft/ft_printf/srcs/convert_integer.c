/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:43:30 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:26:17 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** stdarg makes default argument promotions. That means char and short are
** promoted to int. Hence the int in the va_arg call followed by a cast to
** char or short.
*/

static long long	get_arg_signed(int length, va_list args)
{
	if (length == 0)
		return (va_arg(args, int));
	if (length == len_hh)
		return ((char)va_arg(args, int));
	if (length == len_h)
		return ((short)va_arg(args, int));
	if (length == len_l)
		return (va_arg(args, long));
	return (va_arg(args, long long));
}

static char	*signed_decimal_to_str(t_specs specs, va_list args)
{
	long long	nbr;
	char		*str;

	nbr = get_arg_signed(specs.length, args);
	if (nbr == 0 && specs.precision == 0)
		str = ft_strdup("");
	else
		str = ft_lltoa(nbr);
	if ((specs.flags & (FLAG_PLUS | FLAG_SPACE)) && nbr >= 0)
		str = add_plus_sign_space(str, specs.flags);
	return (str);
}

/*
** stdarg makes default argument promotions. That means char and short are
** promoted to int. Hence the (unsigned) int in the va_arg call followed by a
** cast to (unsigned) char or short.
*/

static unsigned long long	get_arg_unsigned(int length, va_list args)
{
	if (length == 0)
		return (va_arg(args, unsigned int));
	if (length == len_hh)
		return ((unsigned char)va_arg(args, unsigned int));
	if (length == len_h)
		return ((unsigned short)va_arg(args, unsigned int));
	if (length == len_l)
		return (va_arg(args, unsigned long));
	return (va_arg(args, unsigned long long));
}

static char	*unsigned_to_str(t_specs specs, va_list args)
{
	unsigned long long	nbr;
	char				*str;

	nbr = get_arg_unsigned(specs.length, args);
	if (nbr == 0 && specs.precision == 0)
		str = ft_strdup("");
	else if (specs.type == c_unsigned_decimal)
		str = ft_utoa_base(nbr, "0123456789");
	else if (specs.type == c_octal)
		str = ft_utoa_base(nbr, "01234567");
	else if (specs.type == c_hexa_lower)
		str = ft_utoa_base(nbr, "0123456789abcdef");
	else
		str = ft_utoa_base(nbr, "0123456789ABCDEF");
	if (specs.flags & FLAG_HASH)
		str = insert_prefix(str, specs.type, nbr);
	return (str);
}

/*
** Handles the d, i, o, u, x and X types convertions.
** Outputs to stdout the converted string with ajusted precision, width,
** aligment and zero padding (if applicable).
** Returns the number of charactes written or -1 if error.
*/

int	convert_integer(t_specs specs, va_list args)
{
	char			*str;
	int				ret;

	if (specs.type == c_decimal || specs.type == c_integer)
		str = signed_decimal_to_str(specs, args);
	else
		str = unsigned_to_str(specs, args);
	if (!str)
		return (-1);
	str = adjust_precision(str, specs.precision);
	if (!str)
		return (-1);
	if ((specs.flags & FLAG_0) && specs.precision < 0)
		str = adjust_0_width_numeric(str, specs.width);
	else
		str = adjust_width_align(str, specs);
	if (!str)
		return (-1);
	ret = write(1, str, ft_strlen(str));
	free(str);
	return (ret);
}
