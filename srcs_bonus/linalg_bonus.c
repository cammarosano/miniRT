/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:36:16 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 17:35:39 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg_bonus.h"

double	dot(t_vect v, t_vect w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vect	cross(t_vect a, t_vect b)
{
	t_vect	r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return (r);
}

t_vect	v_scale(double k, t_vect v)
{
	t_vect	r;

	r.x = k * v.x;
	r.y = k * v.y;
	r.z = k * v.z;
	return (r);
}

t_vect	v_subtract(t_vect dest, t_vect origin)
{
	t_vect	v;

	v.x = dest.x - origin.x;
	v.y = dest.y - origin.y;
	v.z = dest.z - origin.z;
	return (v);
}

t_vect	v_add(t_vect v, t_vect w)
{
	t_vect	r;

	r.x = v.x + w.x;
	r.y = v.y + w.y;
	r.z = v.z + w.z;
	return (r);
}
