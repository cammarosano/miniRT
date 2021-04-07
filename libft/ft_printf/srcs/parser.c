/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:30:03 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 14:09:00 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Parses the "0-+ #" flags and moves the pointer forward.
** A MINUS flag overrides the 0 flag.
** A PLUS flag overrides the SPACE flag.
*/

static void	parse_flags(const char **ptr, int *flags)
{
	while (is_in_charset(**ptr, "0-+ #"))
	{
		if (**ptr == '0')
			*flags |= FLAG_0;
		else if (**ptr == '-')
			*flags |= FLAG_MINUS;
		else if (**ptr == ' ')
			*flags |= FLAG_SPACE;
		else if (**ptr == '+')
			*flags |= FLAG_PLUS;
		else if (**ptr == '#')
			*flags |= FLAG_HASH;
		(*ptr)++;
	}
	if (*flags & FLAG_MINUS)
		*flags &= ~FLAG_0;
	if (*flags & FLAG_PLUS)
		*flags &= ~FLAG_SPACE;
}

/*
** Parses the width specification and moves the pointer forward.
** If a negative value is informed via the "*" in the argument, FLAG_MINUS gets
** switched on, and width becomes the absolute value.
*/

static void	parse_width(const char **ptr, t_specs *specs, va_list args)
{
	int	width;

	if (**ptr == '*')
	{
		width = va_arg(args, int);
		if (width < 0)
		{
			specs->width = -width;
			specs->flags |= FLAG_MINUS;
			specs->flags &= ~FLAG_0;
		}
		else
			specs->width = width;
		(*ptr)++;
	}
	else if (**ptr >= '1' && **ptr <= '9')
		specs->width = parse_decimal_str(ptr);
}

/*
** Parses the precision specification and moves the pointer forward.
** Precision becomes zero if no digits follow the dot.
*/

static void	parse_precision(const char **ptr, t_specs *specs, va_list args)
{
	if (**ptr != '.')
		return ;
	(*ptr)++;
	if (**ptr == '*')
	{
		specs->precision = va_arg(args, int);
		(*ptr)++;
	}
	else
		specs->precision = parse_decimal_str(ptr);
}

/*
** Parses the conversion type specification.
** The pointer is moved forward only if the conversion type is matched
** to one of the listed characters.
** Type gets the value -1 if no conversion match.
*/

static void	parse_type(const char **ptr, t_specs *specs)
{
	char	*conversions;
	char	type;
	int		i;

	conversions = "cspdiouxXfegn\',;:_jtzqLvDOUEFGaACS";
	type = **ptr;
	i = -1;
	while (conversions[++i])
	{
		if (conversions[i] == type)
		{
			specs->type = i;
			(*ptr)++;
			return ;
		}
	}
	specs->type = -1;
}

/*
** Parses the "0-+ #" flags, width and precision specifiers, length modifier
** (l, ll, h, hh) and conversion type specifier into the structure pointed by
** specs.
*/

void	parse_specs(const char **ptr, t_specs *specs, va_list args)
{
	(*ptr)++;
	specs->flags = 0;
	specs->width = 0;
	specs->precision = -1;
	specs->length = 0;
	while (ft_isdigit(**ptr) || is_in_charset(**ptr, "-.*+ #hl"))
	{
		parse_flags(ptr, &(specs->flags));
		parse_width(ptr, specs, args);
		parse_precision(ptr, specs, args);
		parse_length(ptr, specs);
	}
	parse_type(ptr, specs);
}
