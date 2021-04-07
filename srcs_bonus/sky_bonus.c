/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:06:35 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 15:52:01 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vect	night_sky(t_vect ray, t_scene *scene)
{
	double	r;
	double	g;
	double	b;

	if ((int)((ray.x * ray.y * ray.z) * 10e09) %
		(40 * (1 + 500 * !scene->res.antialias)) == 0)
		return (v_scale(fabs(ray.y), vector(1, 1, 1)));
	if (ray.z < 0)
		return (vector(0, 0, 0));
	r = ray.z * 0.01;
	g = 0;
	b = ray.z * 0.05;
	return (vector(r, g, b));
}

t_vect	blue_sky(t_vect ray)
{
	double	r;
	double	g;
	double	b;

	r = 0.81 - fabs(ray.y) * 0.81;
	g = 0.93 - fabs(ray.y) * 0.46;
	b = 1.0;
	return (vector(r, g, b));
}

t_vect	sky(t_vect ray, t_scene *scene)
{
	if (!scene->sky)
		return (vector(0, 0, 0));
	if (scene->sky == 1)
		return (blue_sky(ray));
	return (night_sky(ray, scene));
}
