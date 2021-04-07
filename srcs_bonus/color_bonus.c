/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:06:45 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 17:49:53 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	clamp(int channel)
{
	if (channel > 255)
		return (255);
	return (channel);
}

static int	sepia_vtoi(t_vect color)
{
	int	red;
	int	green;
	int	blue;

	red = round((color.x * 0.393 + color.y * 0.769 + color.z * 0.189) * 255);
	green = round((color.x * 0.349 + color.y * 0.686 + color.z * 0.168) * 255);
	blue = round((color.x * 0.272 + color.y * 0.534 + color.z * 0.131) * 255);
	red = clamp(red);
	green = clamp(green);
	blue = clamp(blue);
	return (red << 16 | green << 8 | blue);
}

int	color_vtoi(t_vect color, int sepia)
{
	int	red;
	int	green;
	int	blue;

	if (sepia)
		return (sepia_vtoi(color));
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
