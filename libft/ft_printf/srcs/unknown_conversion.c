/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknown_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:46:03 by rcammaro          #+#    #+#             */
/*   Updated: 2021/01/27 14:23:56 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Handles unknown type conversions (when parse_type returns -1).
** Handles the "%" conversion as well.
*/

int	unknown_conversion(t_specs specs, const char **format)
{
	char	*str;
	int		ret;

	if (!**format)
		return (0);
	str = malloc(sizeof(char) * 2);
	if (!str)
		return (-1);
	str[0] = **format;
	str[1] = '\0';
	(*format)++;
	if ((specs.flags & FLAG_0))
		str = adjust_0_width_text(str, specs.width);
	else
		str = adjust_width_align(str, specs);
	if (!str)
		return (-1);
	ret = write(1, str, ft_strlen(str));
	free(str);
	return (ret);
}
