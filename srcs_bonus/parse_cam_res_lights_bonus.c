/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_res_lights_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:51:07 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 14:04:09 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	parse_resolution(char **words, t_scene *scene, int line)
{
	int	width;
	int	height;

	if (scene->res.width != -1)
		return (sc_err(line, "Resolution can only be declared once"));
	if (count_split(words) < 3)
		return (sc_err(line, "Too few arguments for Resolution"));
	if (!parse_int(words[1], &width))
		return (sc_err(line, "Bad format for resolution width"));
	if (!parse_int(words[2], &height))
		return (sc_err(line, "Bad format for resolution height"));
	if (width <= 0 || height <= 0)
		return (sc_err(line, "Resolution width and height must be > 0"));
	scene->res.width = width;
	scene->res.height = height;
	scene->res.antialias = 0;
	if (words[3] && !ft_strcmp(words[3], "--anti-aliasing"))
		scene->res.antialias = 1;
	return (1);
}

int	parse_ambient_light(char **words, t_scene *scene, int line_num)
{
	double	ratio;
	t_vect	color;

	if (scene->ambient.x >= 0)
		return (sc_err(line_num, "Ambient lighting can only be declared once"));
	if (count_split(words) < 3)
		return (sc_err(line_num, "Too few arguments for Ambient lightning"));
	if (!parse_double(words[1], &ratio))
		return (sc_err(line_num, "Bad format for ambient light ratio"));
	if (ratio < 0 || ratio > 1.0)
		return (sc_err(line_num, "Amb light ratio must be in range [0.0,1.0]"));
	if (!parse_color(words[2], &color))
		return (sc_err(line_num, "Bad color format for ambient light"));
	scene->ambient = v_scale(ratio, color);
	if (words[3] && !ft_strcmp(words[3], "--blue-sky"))
		scene->sky = 1;
	else if (words[3] && !ft_strcmp(words[3], "--night-sky"))
		scene->sky = 2;
	return (1);
}

int	parse_camera(char **words, t_scene *scene, int line_num)
{
	t_camera	cam;

	if (count_split(words) < 4)
		return (sc_err(line_num, "Too few arguments for camera"));
	if (!parse_vector(words[1], &cam.position))
		return (sc_err(line_num, "Bad format for camera viewpoint"));
	if (!parse_vector(words[2], &cam.dir))
		return (sc_err(line_num, "Bad format for camera orientation"));
	if (!check_orient_vector(cam.dir))
		return (sc_err(line_num, "Bad values for camera orientation vector"));
	if (!parse_double(words[3], &cam.fov))
		return (sc_err(line_num, "Bad format for camera field of view"));
	if (cam.fov < 0 || cam.fov > 180)
		return (sc_err(line_num, "Camera FOV must be in range [0,180]"));
	cam.sepia_filter = 0;
	if (words[4] && ft_strcmp(words[4], "--sepia") == 0)
		cam.sepia_filter = 1;
	if (!add_camera(&scene->cameras, cam))
		return (syscall_err("add_camera()"));
	return (1);
}

int	parse_lightspot(char **words, t_scene *scene, int line_num)
{
	t_vect	pos_dir;
	double	ratio;
	t_vect	color;
	t_vect	adj_color;
	int		type;

	if (count_split(words) < 4)
		return (sc_err(line_num, "Too few arguments for light spot"));
	if (!parse_vector(words[1], &pos_dir))
		return (sc_err(line_num, "Bad format for light point/direction"));
	if (!parse_double(words[2], &ratio))
		return (sc_err(line_num, "Bad format for light ratio"));
	if (ratio < 0 || ratio > 1.0)
		return (sc_err(line_num, "Light ratio must be in range [0.0, 1.0]"));
	if (!parse_color(words[3], &color))
		return (sc_err(line_num, "Bad format for light color"));
	adj_color = v_scale(ratio, color);
	type = spot;
	if (words[4] && !ft_strcmp(words[4], "--parallel") && v_lenght(pos_dir))
		type = parallel;
	if (!add_lightspot(&scene->lightspots, pos_dir, adj_color, type))
		return (syscall_err("add_lightspot()"));
	return (1);
}
