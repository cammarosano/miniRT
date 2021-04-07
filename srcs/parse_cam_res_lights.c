/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_res_lights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:51:07 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/23 15:21:59 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_resolution(char **words, t_scene *scene, int line)
{
	int	width;
	int	height;

	if (scene->res.width != -1)
		return (sc_err(line, "Resolution can only be declared once"));
	if (!check_n_words(words, line, 3))
		return (sc_err(line, "Too few arguments for Resolution"));
	if (!parse_int(words[1], &width))
		return (sc_err(line, "Bad format for resolution width"));
	if (!parse_int(words[2], &height))
		return (sc_err(line, "Bad format for resolution height"));
	if (width <= 0 || height <= 0)
		return (sc_err(line, "Resolution width and height must be > 0"));
	scene->res.width = width;
	scene->res.height = height;
	return (1);
}

int	parse_ambient_light(char **words, t_scene *scene, int line_num)
{
	double	ratio;
	t_vect	color;

	if (scene->ambient.x >= 0)
		return (sc_err(line_num, "Ambient lighting can only be declared once"));
	if (!check_n_words(words, line_num, 3))
		return (sc_err(line_num, "Too few arguments for Ambient lightning"));
	if (!parse_double(words[1], &ratio))
		return (sc_err(line_num, "Bad format for ambient light ratio"));
	if (ratio < 0 || ratio > 1.0)
		return (sc_err(line_num, "Amb light ratio must be in range [0.0,1.0]"));
	if (!parse_color(words[2], &color))
		return (sc_err(line_num, "Bad color format for ambient light"));
	scene->ambient = v_scale(ratio, color);
	return (1);
}

int	parse_camera(char **words, t_scene *scene, int line_num)
{
	t_vect	position;
	t_vect	dir;
	double	fov;

	if (!check_n_words(words, line_num, 4))
		return (sc_err(line_num, "Too few arguments for camera"));
	if (!parse_vector(words[1], &position))
		return (sc_err(line_num, "Bad format for camera viewpoint"));
	if (!parse_vector(words[2], &dir))
		return (sc_err(line_num, "Bad format for camera orientation"));
	if (!check_orient_vector(dir))
		return (sc_err(line_num, "Bad values for camera orientation vector"));
	if (!parse_double(words[3], &fov))
		return (sc_err(line_num, "Bad format for camera field of view"));
	if (fov < 0 || fov > 180)
		return (sc_err(line_num, "Camera FOV must be in range [0,180]"));
	if (!add_camera(&scene->cameras, position, dir, fov))
		return (syscall_err("add_camera()"));
	return (1);
}

int	parse_lightspot(char **words, t_scene *scene, int line_num)
{
	t_vect	position;
	double	ratio;
	t_vect	color;
	t_vect	adj_color;

	if (!check_n_words(words, line_num, 4))
		return (sc_err(line_num, "Too few arguments for light spot"));
	if (!parse_vector(words[1], &position))
		return (sc_err(line_num, "Bad format for light point"));
	if (!parse_double(words[2], &ratio))
		return (sc_err(line_num, "Bad format for light ratio"));
	if (ratio < 0 || ratio > 1.0)
		return (sc_err(line_num, "Light ratio must be in range [0.0, 1.0]"));
	if (!parse_color(words[3], &color))
		return (sc_err(line_num, "Bad format for light spot color"));
	adj_color = v_scale(ratio, color);
	if (!add_lightspot(&scene->lightspots, position, adj_color))
		return (syscall_err("add_lightspot()"));
	return (1);
}
