/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:31:57 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:35:16 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Works as adjust_0_width_numeric, except that it ignores +, - or space,
** padding 0s starting from the left side.
*/

char	*adjust_0_width_text(char *src, int width)
{
	char	*dst;
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
	i = 0;
	while (i < width - len)
		dst[i++] = '0';
	dst[i] = '\0';
	ft_strlcat(dst, src, width + 1);
	free(src);
	return (dst);
}

/*
** Adds a space or a plus sign to the left of "src".
** The caller must assure that one of the PLUS and SPACE flags are switched on,
** and that "src" represents a positive number.
** Frees "src" and returns a freeble string
** (or the NULL pointer if malloc error, see ft_strjoin).
*/

char	*add_plus_sign_space(char *src, int flags)
{
	char	*dst;

	if (!src)
		return (NULL);
	if (flags & FLAG_PLUS)
		dst = ft_strjoin("+", src);
	else
		dst = ft_strjoin(" ", src);
	free(src);
	return (dst);
}

/*
** Inserts the prefix to left of "src", according the conversion type,
** in order to satisfy the "#" flag.
*/

char	*insert_prefix(char *src, int conv_type, unsigned long long nbr)
{
	char	*dst;

	if (!src)
		return (NULL);
	if (conv_type == c_octal && *src != '0')
		dst = ft_strjoin("0", src);
	else if (conv_type == c_hexa_lower && nbr)
		dst = ft_strjoin("0x", src);
	else if (conv_type == c_hexa_upper && nbr)
		dst = ft_strjoin("0X", src);
	else
		return (src);
	free(src);
	return (dst);
}

/*
** Trims the "target" character (0 or multiple occurences) from the source
** string from the right only, by replacing it by '\0'.
** Thus, "src" must point to writable memory.
*/

void	trim_from_right(char *src, char target)
{
	size_t	len;

	if (!src)
		return ;
	len = ft_strlen(src);
	src += len;
	while (len-- && *--src == target)
		*src = '\0';
}
