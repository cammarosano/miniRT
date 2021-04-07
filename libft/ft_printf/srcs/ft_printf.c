/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:14:55 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 14:15:05 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Parses conversion specifications into a structure then calls the suitable
** function to output the converted string.
** Returns the number of bytes written (output), or -1 if error.
*/

static int	convert(const char **s, va_list args, int counter)
{
	t_specs	specs;

	parse_specs(s, &specs, args);
	if (specs.type == c_char)
		return (convert_char(specs, args));
	if (specs.type == c_string)
		return (convert_string(specs, args));
	if (specs.type == c_pointer)
		return (convert_pointer(specs, args));
	if (specs.type >= c_decimal && specs.type <= c_hexa_upper)
		return (convert_integer(specs, args));
	if (specs.type >= c_float && specs.type <= c_signficant)
		return (convert_float(specs, args));
	if (specs.type == c_store_number)
		return (convert_n(specs.length, args, counter));
	if (specs.type > c_store_number)
		return (unsuported("(unsuported conversion)"));
	return (unknown_conversion(specs, s));
}

/*
** Writes to stdout the content of a string up to '\0' or '%' (not included),
** and moves the pointer to this character.
** Returns the number of characters output.
*/

static int	putstr_move(const char **str)
{
	size_t		len;
	const char	*ptr;

	ptr = *str;
	len = 0;
	while (**str && **str != '%')
	{
		(*str)++;
		len++;
	}
	return (write(1, ptr, len));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;
	int		counter;

	if (!format)
		return (-1);
	va_start(args, format);
	counter = 0;
	while (*format)
	{
		counter += putstr_move(&format);
		if (*format == '%')
		{
			ret = convert(&format, args, counter);
			if (ret == -1)
				return (va_end_return(args));
			counter += ret;
		}
	}
	va_end(args);
	return (counter);
}
