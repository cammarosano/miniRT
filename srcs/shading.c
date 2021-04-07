/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 02:08:43 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 17:39:29 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vect	diffuse_component(t_vect nd_shadow_ray, t_vect surf_norm,
							t_vect spot_adj_color, t_vect obj_color)
{
	double	diffuse_factor;
	t_vect	result;

	diffuse_factor = fmax(0, dot(nd_shadow_ray, surf_norm));
	result = color_multiply(spot_adj_color, obj_color);
	result = v_scale(diffuse_factor, result);
	return (result);
}

static t_vect	specular_refl(t_vect nd_shadow_ray, t_hit_point *hp,
						t_vect spot_adj_color, t_vect nd_view_ray)
{
	t_vect	inv_reflected_ray;
	double	cos_refl_prim_ray;
	t_vect	result;

	inv_reflected_ray = reflected(nd_shadow_ray, hp->surf_normal);
	cos_refl_prim_ray = fmax(0, dot(nd_view_ray, inv_reflected_ray));
	result = v_scale(pow(cos_refl_prim_ray, hp->shine), spot_adj_color);
	result = v_scale(SPEC_REFL_COEF * log(hp->shine), result);
	return (result);
}

/*
** Cast a shadow ray from hp to lightspot and check if point is shadowed by any
** object in the scene. If not, calculate diffuse reflection and specular
** reflection contributions of that lightspot to hp.
*/

static t_vect	cast_shadow_ray(t_spot *lightspot, t_hit_point *hp,
								t_list *obj_list, t_vect view_ray)
{
	t_vect	shadow_ray;
	t_vect	result_color;
	t_obj	*obj;

	shadow_ray = v_subtract(lightspot->position, hp->point);
	if (v_lenght(shadow_ray) < EPSILON)
		return (vector(0, 0, 0));
	while (obj_list)
	{
		obj = obj_list->content;
		if (intercept_obj(hp->point, shadow_ray, obj, EPSILON) < 1.0)
			return (vector(0, 0, 0));
		obj_list = obj_list->next;
	}
	shadow_ray = v_normalize(shadow_ray);
	result_color = diffuse_component(shadow_ray, hp->surf_normal,
			lightspot->adj_color, hp->obj_color);
	result_color = v_add(result_color, specular_refl(shadow_ray, hp,
				lightspot->adj_color, view_ray));
	return (result_color);
}

/*
** Calculate the resulting color at point, adding contributions from ambient
** lighting and each lightspot in the scene, by casting shadow rays
*/

t_vect	calc_shading(t_scene *scene, t_vect ray, t_hit_point *point)
{
	t_list	*spots_list;
	t_spot	*lightspot;
	t_vect	color;

	color = color_multiply(scene->ambient, point->obj_color);
	spots_list = scene->lightspots;
	while (spots_list)
	{
		lightspot = spots_list->content;
		color = v_add(color, cast_shadow_ray(lightspot, point,
					scene->objects, ray));
		spots_list = spots_list->next;
	}
	return (color);
}
