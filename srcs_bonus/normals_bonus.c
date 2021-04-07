/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:02:19 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 14:03:59 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vect	normal_sphere(void *shape, t_vect point)
{
	t_sphere	*s;

	s = shape;
	return (v_scale(1 / s->radius, v_subtract(point, s->center)));
}

t_vect	normal_plane(void *shape, t_vect point)
{
	t_plane	*p;

	p = shape;
	(void)point;
	return (p->normal);
}

t_vect	normal_triangle(void *shape, t_vect point)
{
	t_triangle	*tr;

	tr = shape;
	(void)point;
	return (tr->normal);
}

t_vect	normal_square(void *shape, t_vect point)
{
	t_square	*sq;

	sq = shape;
	(void)point;
	return (sq->normal);
}

t_vect	normal_cylinder(void *shape, t_vect point)
{
	t_cylinder	*cyl;
	t_vect		op;
	t_vect		tangent;

	cyl = shape;
	op = v_subtract(point, cyl->center);
	tangent = cross(op, cyl->dir);
	return (v_normalize(cross(cyl->dir, tangent)));
}
