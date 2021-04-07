/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:53:52 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:17:32 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Calculate the color of a pixel by casting a ray and checking for
** interceptions with objects in the scene. In case of hit, calculate shading.
*/

static t_vect	cast_ray(t_vect origin, t_vect dir, t_scene *scene)
{
	t_hit_point	hit_point;
	t_vect		local_color;

	if (check_interception(origin, dir, scene->objects, &hit_point) == 0)
		return (vector(0, 0, 0));
	local_color = calc_shading(scene, dir, &hit_point);
	return (local_color);
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

/*
** scale_factor = 2 * tan(fov/2) / res.width
** One unit in pixel coordinates correspondes to scale_fator in the view pane,
** which is located 1 unit away (scene coordinates) from the camera position.
** half_s stores half of the scale_factor.
*/

static void	setup_cam(t_camera *cam, t_resol res)
{
	t_vect	up;
	t_vect	u;
	t_vect	v;
	t_vect	w;

	up = vector(0, 1, 0);
	w = v_normalize(cam->dir);
	u = cross(w, up);
	if (v_lenght(u) < 1.0e-50)
		u = vector(1, 0, 0);
	v = cross(u, w);
	cam->dir = w;
	cam->u = v_normalize(u);
	cam->v = v_normalize(v);
	cam->half_s = tan(deg_to_rad(cam->fov) * 0.5) / res.width;
}

void	render(t_camera *camera, t_img *img, t_scene *scene,
						void (*put_pixel)(t_img *, int, int, int))
{
	int		x;
	int		y;
	t_vect	color;
	t_vect	ray_dir;

	setup_cam(camera, scene->res);
	y = 0;
	while (y < scene->res.height)
	{
		x = 0;
		while (x < scene->res.width)
		{
			ray_dir = calc_vector_dir(x, y, camera, scene->res);
			color = cast_ray(camera->position, ray_dir, scene);
			put_pixel(img, x, y, color_vtoi(color));
			x++;
		}
		y++;
	}
}
