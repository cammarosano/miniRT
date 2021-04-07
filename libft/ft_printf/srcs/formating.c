/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 02:05:14 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:33:33 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	define_prefix(char *src)
{
	if (*src == '-' || *src == '+' || *src == ' ')
		return (1);
	if (src[0] == '0' && (src[1] == 'x' || src[1] == 'X'))
		return (2);
	return (0);
}

/*
** Inserts 0s to the left in order to ajust precision for interger conversions.
** "src" argument must be a freeable string.
** Handles the negative and positive signs, the space and the 0x and 0X
** prefixes.
** Returns the source string if no change to be made. Otherwise, frees the
** source string (src) and returns a feeable pointer.
** Returns the null pointer in case of malloc error.
*/

char	*adjust_precision(char *src, int precision)
{
	int		prefix;
	int		n_digits;
	char	*dst;
	int		i;

	prefix = define_prefix(src);
	n_digits = ft_strlen(src) - prefix;
	if (precision <= n_digits)
		return (src);
	dst = malloc(sizeof(char) * (precision + prefix + 1));
	if (!dst)
		return (free_return_null(src));
	i = -1;
	while (++i < prefix)
		dst[i] = src[i];
	while (i < precision - n_digits + prefix)
		dst[i++] = '0';
	dst[i] = '\0';
	ft_strlcat(dst, src + prefix, precision + prefix + 1);
	free(src);
	return (dst);
}

static void	fill_spaces(char *dst, unsigned int n)
{
	while (n--)
		*dst++ = ' ';
	*dst = '\0';
}

/*
** Pads with spaces according to informed width and aligment (flags).
** "src" argument must be a freeable string.
** Returns the source string if no change to be made. Otherwise, frees the
** source string (src) and returns a feeable pointer.
** Returns the null pointer in case of malloc error.
*/

char	*adjust_width_align(char *src, t_specs specs)
{
	int		size;
	int		len;
	char	*dst;

	if (specs.width < 0)
		return (free_return_null(src));
	len = ft_strlen(src);
	size = specs.width;
	if (size <= len)
		return (src);
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (free_return_null(src));
	if ((specs.flags & FLAG_MINUS))
	{
		ft_strlcpy(dst, src, size + 1);
		fill_spaces(dst + len, size - len);
	}
	else
	{
		fill_spaces(dst, size - len);
		ft_strlcat(dst, src, size + 1);
	}
	free(src);
	return (dst);
}

/*
** Pads with zeros to the left according to width.
** Handles the negative and positives signs, the space and the "0x" as
** prefixes, inserting the zeros between the prefix and the digits.
** "src" argument must be a freeable string.
** Returns the source string if no change to be made. Otherwise, frees the
** source string (src) and returns a feeable pointer.
** Returns the null pointer in case of malloc error.
*/

char	*adjust_0_width_numeric(char *src, int width)
{
	char	*dst;
	int		prefix;
	int		len;
	int		i;

	if (width < 0)
		return (free_return_null(src));
	len = ft_strlen(src);
	if (width <= len)
		return (src);
	dst = malloc(sizeof(char) * (width + 1));
	if (!dst)
		return (free_return_null(src));
	prefix = define_prefix(src);
	i = -1;
	while (++i < prefix)
		dst[i] = src[i];
	while (i < width - len + prefix)
		dst[i++] = '0';
	dst[i] = '\0';
	ft_strlcat(dst, src + prefix, width + 1);
	free(src);
	return (dst);
}
