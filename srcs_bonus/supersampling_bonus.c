/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:06:52 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:26:14 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vect	calc_vector_dir_fl(double x, double y, t_camera *cam,
									t_resol res)
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

static t_vect	sample_16(int x, int y, t_camera *cam, t_scene *scene)
{
	static double	delta[4] = {-0.375, -0.125, +0.125, +0.375};
	int				i;
	int				j;
	t_vect			ray;
	t_vect			color;

	color = vector(0, 0, 0);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ray = calc_vector_dir_fl(x + delta[i], y + delta[j], cam,
					scene->res);
			color = v_add(color, cast_ray(cam->position, ray, scene, BOUNCES));
			j++;
		}
		i++;
	}
	color = v_scale(1.0 / 16, color);
	return (color);
}

static double	biggest_diff(t_vect *color, t_vect average)
{
	double	max_diff;
	int		i;

	max_diff = 0;
	i = -1;
	while (++i < 4)
		if (fabs(color[i].x - average.x) > max_diff)
			max_diff = color[i].x - average.x;
	i = -1;
	while (++i < 4)
		if (fabs(color[i].y - average.y) > max_diff)
			max_diff = color[i].y - average.y;
	i = -1;
	while (++i < 4)
		if (fabs(color[i].z - average.z) > max_diff)
			max_diff = color[i].z - average.z;
	return (max_diff);
}

static t_vect	average_color(t_vect *color)
{
	t_vect	sum;
	int		i;

	sum = vector(0, 0, 0);
	i = 0;
	while (i < 4)
		sum = v_add(sum, color[i++]);
	return (v_scale(0.25, sum));
}

/*
** Samples 4 points in the pixel and checks if the difference from any point
** to their average is bigger than AALIAS_THRSHD (in any of the three RGB
** channels). If not, return the average color.
** If yes, proceed to sample 16 points.
*/

t_vect	adapt_super_sample(int x, int y, t_camera *cam, t_scene *scene)
{
	t_vect	color[4];
	t_vect	ray;
	t_vect	average;

	ray = calc_vector_dir_fl(x - 0.25, y - 0.25, cam, scene->res);
	color[0] = cast_ray(cam->position, ray, scene, BOUNCES);
	ray = calc_vector_dir_fl(x + 0.25, y - 0.25, cam, scene->res);
	color[1] = cast_ray(cam->position, ray, scene, BOUNCES);
	ray = calc_vector_dir_fl(x - 0.25, y + 0.25, cam, scene->res);
	color[2] = cast_ray(cam->position, ray, scene, BOUNCES);
	ray = calc_vector_dir_fl(x + 0.25, y + 0.25, cam, scene->res);
	color[3] = cast_ray(cam->position, ray, scene, BOUNCES);
	average = average_color(color);
	if (biggest_diff(color, average) > AALIAS_THRSHD)
		return (sample_16(x, y, cam, scene));
	return (average);
}
