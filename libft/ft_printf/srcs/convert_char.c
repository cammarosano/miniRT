/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 21:51:47 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:16:31 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	put_padded_char(char *buffer, int n_bytes, t_specs specs)
{
	int		padding_size;
	int		total_size;
	char	pad;

	if (specs.width < 0)
		return (-1);
	total_size = specs.width;
	if (total_size < n_bytes)
		total_size = n_bytes;
	padding_size = total_size - n_bytes;
	pad = ' ';
	if (specs.flags & FLAG_0)
		pad = '0';
	while (!(specs.flags & FLAG_MINUS) && padding_size--)
		write(1, &pad, 1);
	if (write(1, buffer, n_bytes) == -1)
		return (-1);
	while ((specs.flags & FLAG_MINUS) && padding_size--)
		write(1, &pad, 1);
	return (total_size);
}

/*
** Handles the narrow and wide character convertions (%c and %lc).
** c: the int argument is converted to an unsigned char.
** lc: the wint_t argument is converted to wchar_t, which is in turn converted
** to a multi-byte sequence (UTF-8 encoding).
** Outputs to stdout the character resulting from conversion with ajusted
** width, zero padding and aligment.
** Returns the number of BYTES (not characters) written or -1 if error.
** The null-character is handled.
*/

int	convert_char(t_specs specs, va_list args)
{
	wchar_t			wc;
	char			buffer[4];
	int				n_bytes;

	if (specs.length == len_l)
	{
		wc = (wchar_t)va_arg(args, wint_t);
		n_bytes = ft_wchar_to_mb(buffer, wc);
		if (!n_bytes)
			return (-1);
		return (put_padded_char(buffer, n_bytes, specs));
	}
	*buffer = (unsigned char)va_arg(args, int);
	return (put_padded_char(buffer, 1, specs));
}
