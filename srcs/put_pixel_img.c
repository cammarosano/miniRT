/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:52:43 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/23 01:53:18 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** X-Server's computer is big endian;
*/

void	put_pixel_mlx_be(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		y_offset;
	int		x_offset;
	int		byte_offset;

	x_offset = x * (img->bits_ppx / 8);
	y_offset = y * img->size_line;
	byte_offset = (img->bits_ppx - 24) / 8;
	dst = img->addr + y_offset + x_offset;
	dst[0] = 0;
	dst[0 + byte_offset] = color >> 16;
	dst[1 + byte_offset] = color >> 8;
	dst[2 + byte_offset] = color;
}

/*
** X-Server's computer is little endian;
*/

void	put_pixel_mlx_le(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		y_offset;
	int		x_offset;

	x_offset = x * (img->bits_ppx / 8);
	y_offset = y * img->size_line;
	dst = img->addr + y_offset + x_offset;
	dst[0] = color;
	dst[1] = color >> 8;
	dst[2] = color >> 16;
}

/*
** The BMP format specifies little-endianess.
** Output bmp file has 24 bits per pixel color depth.
*/

void	put_pixel_bmp(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		y_offset;
	int		x_offset;

	x_offset = x * 3;
	y_offset = (img->height - 1 - y) * img->size_line;
	dst = img->addr + y_offset + x_offset;
	dst[0] = color;
	dst[1] = color >> 8;
	dst[2] = color >> 16;
}
