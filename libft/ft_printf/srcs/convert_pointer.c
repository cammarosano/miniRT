/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:07:50 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:38:18 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static char	*add_prefix(char *src)
{
	char	*dst;

	dst = ft_strjoin("0x", src);
	free(src);
	return (dst);
}

static char	*address_to_str(t_specs specs, va_list args)
{
	unsigned long long	nbr;

	nbr = (unsigned long long)va_arg(args, void *);
	if (nbr == 0 && specs.precision == 0)
		return (ft_strdup(""));
	else
		return (ft_utoa_base(nbr, "0123456789abcdef"));
}

/*
** Handles the %p convertion.
** Outputs to stdout the conversion result with ajusted precision, width,
** aligment and zero padding (if applicable).
** Pointer address is prefixed by "0x".
** Returns the number of characters written or -1 if error.
*/

int	convert_pointer(t_specs specs, va_list args)
{
	char				*str;
	int					ret;

	str = address_to_str(specs, args);
	if (!str)
		return (-1);
	str = adjust_precision(str, specs.precision);
	if (!str)
		return (-1);
	str = add_prefix(str);
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
