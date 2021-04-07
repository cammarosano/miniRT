/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:48:47 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:15:45 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** If src is NULL, resulting string is "(null)".
** If precision was informed (>= 0), src does not have to be null terminated.
*/

static char	*get_string(int precision, char *src)
{
	char	*dst;

	if (!src)
		src = "(null)";
	if (precision < 0)
		return (ft_strdup(src));
	dst = malloc(sizeof(char) * (precision + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, precision + 1);
	return (dst);
}

static char	*append_mb_char(char *src, char *buffer, int n_bytes)
{
	char	*dst;

	buffer[n_bytes] = '\0';
	dst = ft_strjoin(src, buffer);
	free(src);
	return (dst);
}

/*
** Each wchar is converted to a multibyte sequence (UTF-8 encoding),
** up to "precision" bytes (if precision has been informed) or the NULL wchar
** (L'\0').
** If src is NULL, resulting string is "(null)".
** If precision was informed (>= 0), src does not have to be null terminated.
*/

static char	*get_wstring(int precision, wchar_t *src)
{
	char	*dst;
	char	buffer[5];
	char	byte_count;
	int		ret;

	if (!src)
		src = L"(null)";
	dst = ft_strdup("");
	if (!dst)
		return (NULL);
	byte_count = 0;
	while (*src && (precision < 0 || byte_count < precision))
	{
		ret = ft_wchar_to_mb(buffer, *src++);
		if (!ret)
			return (free_return_null(dst));
		byte_count += ret;
		if (precision >= 0 && byte_count > precision)
			break ;
		dst = append_mb_char(dst, buffer, ret);
		if (!dst)
			return (NULL);
	}
	return (dst);
}

/*
** Handles the %s (string) and %ls (wide char string) convertions.
** Outputs to stdout the string with ajusted precision, width and aligment.
** Returns the number of BYTES (not characters) written or -1 if error.
*/

int	convert_string(t_specs specs, va_list args)
{
	char	*str;
	int		ret;

	if (specs.length == len_l)
		str = get_wstring(specs.precision, va_arg(args, wchar_t *));
	else
		str = get_string(specs.precision, va_arg(args, char *));
	if (!str)
		return (-1);
	if (specs.flags & FLAG_0)
		str = adjust_0_width_text(str, specs.width);
	else
		str = adjust_width_align(str, specs);
	if (!str)
		return (-1);
	ret = write(1, str, ft_strlen(str));
	free(str);
	return (ret);
}
