/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:26:55 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/23 19:04:21 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <wchar.h>

/*
** ft_printf: formatted output conversion.
** ft_lltoa: integer to string (decimal base).
** ft_utoa_base: unsigned integer to string in any base.
** ft_wchar_to_mb: wide char (Unicode code point) to multi-byte sequence
**                 (UTF-8 encoding).
*/

int		ft_printf(const char *format, ...);
char	*ft_lltoa(long long n);
char	*ft_utoa_base(unsigned long long nbr, char *base);
int		ft_wchar_to_mb(char *buffer, wchar_t code_point);

#endif
