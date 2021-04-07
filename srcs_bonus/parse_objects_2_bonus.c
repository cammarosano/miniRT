/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:05:23 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 15:55:06 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	load_uv_coords_sq(t_square *sq)
{
	t_vect	u;
	t_vect	v;
	t_vect	up;

	up = vector(0, 1, 0);
	sq->normal = v_normalize(sq->normal);
	u = cross(up, sq->normal);
	if (v_lenght(u) < EPSILON)
		u = vector(1, 0, 0);
	v = cross(sq->normal, u);
	sq->u = v_normalize(u);
	sq->v = v_normalize(v);
}

int			parse_square(char **words, t_scene *scene, int line_num)
{
	t_obj		obj;
	t_square	sq;

	if (count_split(words) < 5)
		return (sc_err(line_num, "Too few arguments for square"));
	if (!parse_vector(words[1], &sq.center))
		return (sc_err(line_num, "Bad format for square center coordinates"));
	if (!parse_vector(words[2], &sq.normal))
		return (sc_err(line_num, "Bad format for square orientation vector"));
	if (!check_orient_vector(sq.normal))
		return (sc_err(line_num, "Bad values for square orientation vector"));
	if (!parse_double(words[3], &sq.side))
		return (sc_err(line_num, "Bad format for square side size"));
	if ((sq.side < 0))
		return (sc_err(line_num, "Square side size must be positive number"));
	if (!parse_color(words[4], &obj.color))
		return (sc_err(line_num, "Bad format for square color"));
	load_uv_coords_sq(&sq);
	parse_extras(&words[5], &obj);
	if (!add_square(&scene->objects, obj, sq))
		return (0);
	return (1);
}

int			parse_cube(char **words, t_scene *scene, int line)
{
	t_obj		obj;
	t_square	cube;

	if (count_split(words) < 5)
		return (sc_err(line, "Too few arguments for cube"));
	if (!parse_vector(words[1], &cube.center))
		return (sc_err(line, "Bad format for cube center coordinates"));
	if (!parse_vector(words[2], &cube.normal))
		return (sc_err(line, "Bad format for cube orientation vector"));
	if (!check_orient_vector(cube.normal))
		return (sc_err(line, "Bad values for cube orientation vector"));
	if (!parse_double(words[3], &cube.side))
		return (sc_err(line, "Bad format for cube side size"));
	if ((cube.side < 0))
		return (sc_err(line, "Cube side size must be positive number"));
	if (!parse_color(words[4], &obj.color))
		return (sc_err(line, "Bad format for cube color"));
	load_uv_coords_sq(&cube);
	parse_extras(&words[5], &obj);
	if (!add_cube(&scene->objects, obj, cube))
		return (0);
	return (1);
}

int			parse_pyramid(char **words, t_scene *scene, int line)
{
	t_obj		obj;
	t_square	base;
	double		height;

	if (count_split(words) < 6)
		return (sc_err(line, "Too few arguments for pyramid"));
	if (!parse_vector(words[1], &base.center))
		return (sc_err(line, "Bad format for pyramid base center coordinates"));
	if (!parse_vector(words[2], &base.normal))
		return (sc_err(line, "Bad format for pyramid orientation vector"));
	if (!check_orient_vector(base.normal))
		return (sc_err(line, "Bad values for pyramid orientation vector"));
	if (!parse_double(words[3], &base.side))
		return (sc_err(line, "Bad format for pyramid base side size"));
	if (!parse_double(words[4], &height))
		return (sc_err(line, "Bad format for pyramid height"));
	if ((base.side <= 0 || height <= 0))
		return (sc_err(line, "Pyramid base size & height must be positive"));
	if (!parse_color(words[5], &obj.color))
		return (sc_err(line, "Bad format for pyramid color"));
	load_uv_coords_sq(&base);
	parse_extras(&words[5], &obj);
	if (!add_pyramid(&scene->objects, obj, base, height))
		return (0);
	return (1);
}
