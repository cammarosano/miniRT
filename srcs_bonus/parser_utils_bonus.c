/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:36:47 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 14:05:47 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	parse_color(char *str, t_vect *color)
{
	int	r;
	int	g;
	int	b;

	if (!*str)
		return (0);
	r = ft_atoi_mv_ptr(&str);
	if (*str++ != ',')
		return (0);
	g = ft_atoi_mv_ptr(&str);
	if (*str++ != ',')
		return (0);
	b = ft_atoi_mv_ptr(&str);
	if (*str)
		return (0);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->x = (double)r / 255;
	color->y = (double)g / 255;
	color->z = (double)b / 255;
	return (1);
}

/*
** Parses a vector in strict "dd.dd,dd.dd,dd.dd" format
** Returns 1 if format ok, 0 otherwise
*/

int	parse_vector(char *str, t_vect *v)
{
	if (!str || !v)
		return (0);
	v->x = ft_atof_mv_ptr(&str);
	if (*str++ != ',')
		return (0);
	v->y = ft_atof_mv_ptr(&str);
	if (*str++ != ',' || !*str)
		return (0);
	v->z = ft_atof_mv_ptr(&str);
	if (*str)
		return (0);
	return (1);
}

int	parse_double(char *str, double *nbr)
{
	*nbr = ft_atof_mv_ptr(&str);
	if (*str)
		return (0);
	return (1);
}

int	parse_int(char *str, int *nbr)
{
	*nbr = ft_atoi_mv_ptr(&str);
	if (*str)
		return (0);
	return (1);
}
