/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:24:23 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:45:18 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H

# define FT_PRINTF_UTILS_H

# include <stdarg.h>
# include <limits.h>
# include <locale.h>
# include "libft.h"
# include "ft_printf.h"

# define FLAG_0 1
# define FLAG_MINUS 2
# define FLAG_PLUS 4
# define FLAG_SPACE 8
# define FLAG_HASH 16

typedef struct s_specs
{
	int	flags;
	int	width;
	int	precision;
	int	length;
	int	type;
}	t_specs;

enum				e_conversion_type
{
	c_char,
	c_string,
	c_pointer,
	c_decimal,
	c_integer,
	c_octal,
	c_unsigned_decimal,
	c_hexa_lower,
	c_hexa_upper,
	c_float,
	c_scientific,
	c_signficant,
	c_store_number
};

enum				e_length_modifiers
{
	len_h = 1,
	len_hh,
	len_l,
	len_ll
};

void				parse_specs(const char **ptr, t_specs *specs, va_list args);
void				parse_length(const char **ptr, t_specs *specs);
int					parse_decimal_str(const char **ptr);
int					is_in_charset(char c, char *charset);

int					convert_char(t_specs specs, va_list args);
int					convert_string(t_specs specs, va_list args);
int					convert_integer(t_specs specs, va_list args);
int					convert_pointer(t_specs specs, va_list args);
int					convert_float(t_specs specs, va_list args);
int					convert_n(int lenght, va_list args, int counter);
int					unknown_conversion(t_specs specs, const char **format);

char				*adjust_width_align(char *src, t_specs specs);
char				*adjust_precision(char *str, int precision);
char				*adjust_0_width_numeric(char *str, int width);
char				*adjust_0_width_text(char *src, int width);
char				*add_plus_sign_space(char *src, int flags);
void				trim_from_right(char *src, char target);
char				*insert_prefix(char *src, int conv_type,
						unsigned long long nbr);

void				*free_return_null(void *ptr);
int					va_end_return(va_list args);
int					unsuported(char *message);

char				*float_to_str(double nbr, int precision, int flags);
char				*float_to_str_sci(double nbr, int precision, int flags);
char				*float_to_str_signif(double nbr, int precision, int flags);
char				*get_expon_str(int n);
int					test_rounding(double nbr, int precision);
int					check_ull_overflow(double nbr, int precision);
int					resolve_sign_neg(double *nbr);

unsigned long long	ten_power(unsigned int exponent);

#endif
