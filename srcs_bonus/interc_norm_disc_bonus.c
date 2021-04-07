/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interc_norm_disc_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:00:03 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:32:26 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	check_point_in_disc(t_vect point, t_disc *ds)
{
	t_vect	c_p;

	c_p = v_subtract(point, ds->center);
	if (v_lenght(c_p) < ds->radius)
		return (1);
	return (0);
}

double	intercept_disc(t_vect origin, t_vect dir, void *shape, double min)
{
	t_plane	pl;
	t_disc	*ds;
	double	inf;
	double	t;
	t_vect	p;

	ds = shape;
	pl.normal = ds->normal;
	pl.point = ds->center;
	inf = 1.0 / 0.0;
	t = intercept_plane(origin, dir, &pl, min);
	if (!(t < inf))
		return (t);
	p = v_add(origin, v_scale(t, dir));
	if (check_point_in_disc(p, ds))
		return (t);
	return (inf);
}

t_vect	normal_disc(void *shape, t_vect point)
{
	t_disc	*ds;

	ds = shape;
	(void)point;
	return (ds->normal);
}
