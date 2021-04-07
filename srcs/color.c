/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:06:45 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 17:49:48 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	clamp(int channel)
{
	if (channel > 255)
		return (255);
	return (channel);
}

int	color_vtoi(t_vect color)
{
	int	red;
	int	green;
	int	blue;

	red = clamp(round(color.x * 255));
	green = clamp(round(color.y * 255));
	blue = clamp(round(color.z * 255));
	return (red << 16 | green << 8 | blue);
}

t_vect	color_multiply(t_vect a, t_vect b)
{
	t_vect	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	return (r);
}
