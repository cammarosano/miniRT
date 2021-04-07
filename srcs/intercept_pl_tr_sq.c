/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercept_pl_tr_sq.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:39:25 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:00:50 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** plane equation: < (p - p0), n > = 0  (dot product)
** line equation: p = o + t * dir (p and o are points, t a scalar, dir a vector)
*/

double	intercept_plane(t_vect origin, t_vect dir, void *shape, double min)
{
	double	t;
	t_plane	*p;

	p = shape;
	t = dot(v_subtract(p->point, origin), p->normal) / dot(dir, p->normal);
	if (t < min)
		t = 1.0 / 0.0;
	return (t);
}

static int	check_point_in_triangle(t_vect point, t_triangle *tr)
{
	t_vect	vertices;
	t_vect	vertex_p;

	vertices = v_subtract(tr->b, tr->a);
	vertex_p = v_subtract(point, tr->a);
	if (dot(tr->normal, cross(vertices, vertex_p)) < 0)
		return (0);
	vertices = v_subtract(tr->c, tr->b);
	vertex_p = v_subtract(point, tr->b);
	if (dot(tr->normal, cross(vertices, vertex_p)) < 0)
		return (0);
	vertices = v_subtract(tr->a, tr->c);
	vertex_p = v_subtract(point, tr->c);
	if (dot(tr->normal, cross(vertices, vertex_p)) < 0)
		return (0);
	return (1);
}

/*
** Check where line intercepts triangle's plane. Then check if point is
** inside the triangle.
*/

double	intercept_triangle(t_vect origin, t_vect dir, void *shape,
							double min)
{
	t_plane		pl;
	double		t;
	double		inf;
	t_vect		p;
	t_triangle	*tr;

	tr = shape;
	pl.normal = tr->normal;
	pl.point = tr->a;
	inf = 1.0 / 0.0;
	t = intercept_plane(origin, dir, &pl, min);
	if (!(t < inf))
		return (t);
	p = v_add(origin, v_scale(t, dir));
	if (check_point_in_triangle(p, tr))
		return (t);
	return (inf);
}

static int	check_point_in_square(t_vect point, t_square *sq)
{
	double	proj_u;
	double	proj_v;
	t_vect	c_i;

	c_i = v_subtract(point, sq->center);
	proj_u = fabs(dot(c_i, sq->u));
	proj_v = fabs(dot(c_i, sq->v));
	if (proj_u < sq->side / 2 && proj_v < sq->side / 2)
		return (1);
	return (0);
}

/*
** Check where (if) line intercepts square's plane. Then check if point is
** inside the square.
*/

double	intercept_square(t_vect origin, t_vect dir, void *shape, double min)
{
	t_plane		pl;
	double		t;
	double		inf;
	t_vect		p;
	t_square	*sq;

	sq = shape;
	pl.normal = sq->normal;
	pl.point = sq->center;
	inf = 1.0 / 0.0;
	t = intercept_plane(origin, dir, &pl, min);
	if (!(t < inf))
		return (t);
	p = v_add(origin, v_scale(t, dir));
	if (check_point_in_square(p, sq))
		return (t);
	return (inf);
}
