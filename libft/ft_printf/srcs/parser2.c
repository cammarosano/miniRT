/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 01:10:06 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:27:19 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Parses a decimal digits string and moves the pointer to the first non-digit
** character after it.
*/

int	parse_decimal_str(const char **ptr)
{
	int	nbr;

	nbr = 0;
	while (**ptr >= '0' && **ptr <= '9')
	{
		nbr = nbr * 10 + **ptr - '0';
		(*ptr)++;
	}
	return (nbr);
}

int	is_in_charset(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}

/*
** Parses the l, ll, h, and hh length modifiers.
*/

void	parse_length(const char **ptr, t_specs *specs)
{
	while (is_in_charset(**ptr, "lh"))
	{
		if (**ptr == 'l')
		{
			if (specs->length == len_l)
				specs->length = len_ll;
			else
				specs->length = len_l;
		}
		else if (**ptr == 'h')
		{
			if (specs->length == len_h)
				specs->length = len_hh;
			else if (specs->length == 0)
				specs->length = len_h;
		}
		(*ptr)++;
	}
}
