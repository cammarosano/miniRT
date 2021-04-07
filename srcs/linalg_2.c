/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:36:55 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/23 00:41:03 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

double	v_lenght(t_vect v)
{
	return (sqrt(dot(v, v)));
}

t_vect	v_normalize(t_vect v)
{
	t_vect	r;
	double	len;

	len = v_lenght(v);
	r.x = v.x / len;
	r.y = v.y / len;
	r.z = v.z / len;
	return (r);
}

t_vect	vector(double x, double y, double z)
{
	t_vect	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_vect	reflected(t_vect v, t_vect normal)
{
	double	proj_n;

	proj_n = 2 * dot(v, normal);
	return (v_subtract(v, v_scale(proj_n, normal)));
}

double	deg_to_rad(double angle_deg)
{
	return (angle_deg * acos(-1) / 180);
}
