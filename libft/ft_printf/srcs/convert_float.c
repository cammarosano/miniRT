/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:54:58 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:26:41 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdint.h>

/*
** Checks the first bit of the double nbr to check its sign.
** If negative, inverts the sign of nbr and returns 1. Returns 0 otherwise. 
*/

int	resolve_sign_neg(double *nbr)
{
	if (*(int64_t *)nbr >> 63)
	{
		*nbr *= -1;
		return (1);
	}
	return (0);
}

/*
** Checks if nbr is inf, -inf or nan.
** If yes, makes *dst point to a freeable string containing the apropriate
** text and returns 1;
** If not, returns 0.
*/

static int	inf_nan_to_str(double nbr, char **dst)
{
	if (nbr == 1.0 / 0.0)
		*dst = ft_strdup("inf");
	else if (nbr == -1.0 / 0.0)
		*dst = ft_strdup("-inf");
	else if (nbr != nbr)
		*dst = ft_strdup("nan");
	else
		return (0);
	return (1);
}

static char	*get_str(t_specs specs, va_list args, int *inf_or_nan)
{
	double	nbr;
	char	*dst;

	nbr = va_arg(args, double);
	*inf_or_nan = inf_nan_to_str(nbr, &dst);
	if (!*inf_or_nan)
	{
		if (specs.type == c_float)
			dst = float_to_str(nbr, specs.precision, specs.flags);
		else if (specs.type == c_scientific)
			dst = float_to_str_sci(nbr, specs.precision, specs.flags);
		else
			dst = float_to_str_signif(nbr, specs.precision, specs.flags);
	}
	if ((specs.flags & (FLAG_PLUS | FLAG_SPACE)) && nbr >= 0)
		dst = add_plus_sign_space(dst, specs.flags);
	return (dst);
}

/*
** Handles the floating-point conversions %f, %e and %g.
*/

int	convert_float(t_specs specs, va_list args)
{
	char	*str;
	int		ret;
	int		inf_or_nan;

	str = get_str(specs, args, &inf_or_nan);
	if (!str)
		return (-1);
	if (specs.flags & FLAG_0 && !inf_or_nan)
		str = adjust_0_width_numeric(str, specs.width);
	else
		str = adjust_width_align(str, specs);
	if (!str)
		return (-1);
	ret = write(1, str, ft_strlen(str));
	free(str);
	return (ret);
}
