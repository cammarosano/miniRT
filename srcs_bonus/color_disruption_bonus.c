/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruption_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:03:50 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 19:01:23 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

#define ND_FACTOR 0.2
#define DIST_FACTOR 3

t_vect		normal_disruption(t_vect normal, t_obj *obj, t_vect point)
{
	double	dist;
	t_vect	center;
	t_vect	cp;
	double	s;

	if (obj->type == plane)
		center = ((t_plane *)obj->shape)->point;
	else if (obj->type == square)
		center = ((t_square *)obj->shape)->center;
	else
		return (normal);
	cp = v_subtract(point, center);
	dist = v_lenght(cp);
	if (dist < EPSILON)
		return (normal);
	cp = v_normalize(cp);
	s = ND_FACTOR * sin(2 * acos(-1) * (dist / obj->n_disrup_wlen));
	s *= 1 / (1 + dist / (obj->n_disrup_wlen * DIST_FACTOR));
	cp = v_scale(s, cp);
	normal = v_normalize(v_add(normal, cp));
	return (normal);
}

static int	is_black(t_vect u, t_vect v, t_vect cp, double size)
{
	double	coord_u;
	double	coord_v;
	int		res;

	coord_u = dot(cp, u) / size;
	coord_v = dot(cp, v) / size;
	res = ((int)coord_u + (int)coord_v) % 2;
	if (coord_u * coord_v < 0)
		res = !res;
	return (res);
}

int			checker_board(t_obj *obj, t_vect point)
{
	double	size;
	t_vect	u;
	t_vect	v;
	t_vect	center;
	t_vect	cp;

	size = obj->checker_size;
	if (obj->type == square)
	{
		u = ((t_square *)obj->shape)->u;
		v = ((t_square *)obj->shape)->v;
		center = ((t_square *)obj->shape)->center;
	}
	else if (obj->type == plane)
	{
		u = ((t_plane *)obj->shape)->u;
		v = ((t_plane *)obj->shape)->v;
		center = ((t_plane *)obj->shape)->point;
	}
	else
		return (0);
	cp = v_subtract(point, center);
	return (is_black(u, v, cp, size));
}

t_vect		rainbow(t_vect normal)
{
	t_vect	color;

	color.x = fabs(normal.x);
	color.y = fabs(normal.y);
	color.z = fabs(normal.z);
	return (color);
}
