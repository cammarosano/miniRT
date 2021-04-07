/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sample_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:06:31 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 14:06:32 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
** Calculate the color of a pixel by casting a ray and checking for
** interceptions with objects in the scene. In case of hit, calculate shading
** and cast a ray in the reflected direction (recursion).
*/

t_vect	cast_ray(t_vect origin, t_vect dir, t_scene *scene, int bounces)
{
	t_hit_point	hit_point;
	t_vect		local_color;
	t_vect		reflected_color;

	if (check_interception(origin, dir, scene->objects, &hit_point) == 0)
		return (sky(dir, scene));
	local_color = calc_shading(scene, dir, &hit_point);
	if (!bounces || hit_point.reflect < EPSILON)
		return (local_color);
	reflected_color = cast_ray(hit_point.point,
				reflected(dir, hit_point.surf_normal), scene, bounces - 1);
	return (v_add(v_scale(1 - hit_point.reflect, local_color),
					v_scale(hit_point.reflect, reflected_color)));
}

/*
** Calculate direction of a vector from the camera origin to a point on the
** screen with pixel-coordinates x,y.
** Uses the camera's local coordinate system (u and v are perpendicular to
** cam->dir).
*/

t_vect	calc_vector_dir(int x, int y, t_camera *cam, t_resol res)
{
	t_vect	ray;
	double	alpha;
	double	beta;

	alpha = cam->half_s * (2 * x + 1 - res.width);
	beta = cam->half_s * (res.height - 2 * y - 1);
	ray = v_add(cam->dir, v_scale(alpha, cam->u));
	ray = v_add(ray, v_scale(beta, cam->v));
	ray = v_normalize(ray);
	return (ray);
}

t_vect	single_sample(int x, int y, t_camera *cam, t_scene *scene)
{
	t_vect	ray_dir;

	ray_dir = calc_vector_dir(x, y, cam, scene->res);
	return (cast_ray(cam->position, ray_dir, scene, BOUNCES));
}
