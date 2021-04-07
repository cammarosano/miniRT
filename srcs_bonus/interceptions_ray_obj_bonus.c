/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interceptions_ray_obj_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 03:07:30 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:31:55 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	define_obj_light_specs(t_hit_point *hp, t_obj *obj)
{
	hp->shine = obj->shine;
	hp->reflect = obj->reflect;
	hp->obj_color = obj->color;
	if (obj->rainbow)
		hp->obj_color = rainbow(hp->surf_normal);
	if (obj->checker_size > 0 && checker_board(obj, hp->point))
		hp->obj_color = vector(0, 0, 0);
}

/*
** Returns the visible surface normal vector
*/

t_vect	surface_normal(t_obj *obj, t_vect point, t_vect view_ray)
{
	t_vect			normal;
	static	t_vect	(*f[6])(void *, t_vect) = {normal_sphere, normal_plane,
						normal_square, normal_triangle, normal_cylinder,
						normal_disc};

	normal = f[obj->type](obj->shape, point);
	if (dot(normal, view_ray) > 0)
		normal = v_scale(-1, normal);
	if (obj->n_disrup_wlen != 0)
		normal = normal_disruption(normal, obj, point);
	return (normal);
}

/*
** Check if line (p = origin + t * dir) intersects obj.
** Returns t for the closest intersection greater than min, or +inf if no
** intersection.
*/

double	intercept_obj(t_vect origin, t_vect dir, t_obj *obj, double min)
{
	static	double	(*f[6])(t_vect, t_vect, void *, double) = {intercept_sphere,
	intercept_plane, intercept_square, intercept_triangle, intercept_cylinder,
	intercept_disc};

	return (f[obj->type](origin, dir, obj->shape, min));
}

/*
** Check if ray (origin, dir) intercepts any object in the scene.
** Return 0 if no interceptions. Otherwise, return 1 and copy closest
** intersected object's attributes to hit_point.
*/

int	check_interception(t_vect origin, t_vect dir, t_list *obj_list,
								t_hit_point *hp)
{
	double	t;
	double	closest_t;
	t_obj	*closest_obj;
	t_obj	*obj;

	closest_t = 1.0 / 0.0;
	closest_obj = NULL;
	while (obj_list)
	{
		obj = obj_list->content;
		t = intercept_obj(origin, dir, obj, EPSILON);
		if (t < closest_t)
		{
			closest_t = t;
			closest_obj = obj;
		}
		obj_list = obj_list->next;
	}
	if (!closest_obj)
		return (0);
	hp->point = v_add(origin, v_scale(closest_t, dir));
	hp->surf_normal = surface_normal(closest_obj, hp->point, dir);
	define_obj_light_specs(hp, closest_obj);
	return (1);
}
