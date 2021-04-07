/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:25:27 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:13:05 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(char **words, t_scene *scene, int line_num)
{
	int			ret;
	t_sphere	sp;
	t_obj		obj;

	if (!check_n_words(words, line_num, 4))
		return (sc_err(line_num, "Too few arguments for sphere"));
	ret = parse_vector(words[1], &sp.center);
	if (!ret)
		return (sc_err(line_num, "Bad format for shere center"));
	if (!parse_double(words[2], &sp.radius))
		return (sc_err(line_num, "Bad format for sphere diameter"));
	if (sp.radius < 0)
		return (sc_err(line_num, "Sphere diameter must be positive number"));
	sp.radius /= 2;
	if (!parse_color(words[3], &obj.color))
		return (sc_err(line_num, "Bad format for sphere color"));
	obj.shine = SP_SHINE;
	ret = add_sphere(&scene->objects, obj, sp);
	if (!ret)
		return (0);
	return (1);
}

int	parse_plane(char **words, t_scene *scene, int line_num)
{
	t_plane	pl;
	t_obj	obj;

	if (!check_n_words(words, line_num, 4))
		return (sc_err(line_num, "Too few arguments for plane"));
	if (!parse_vector(words[1], &pl.point))
		return (sc_err(line_num, "Bad format for point in plane"));
	if (!parse_vector(words[2], &pl.normal))
		return (sc_err(line_num, "Bad format for plane orientation"));
	if (!check_orient_vector(pl.normal))
		return (sc_err(line_num, "Bad values for plane orientation vector"));
	if (!parse_color(words[3], &obj.color))
		return (sc_err(line_num, "Bad format for plane color"));
	obj.shine = PL_SHINE;
	if (!add_plane(&scene->objects, obj, pl))
		return (0);
	return (1);
}

int	parse_triangle(char **words, t_scene *scene, int line_num)
{
	t_obj		obj;
	t_triangle	tr;

	if (!check_n_words(words, line_num, 5))
		return (sc_err(line_num, "Too few arguments for triangle"));
	if (!parse_vector(words[1], &tr.a) || !parse_vector(words[2], &tr.b)
		|| !parse_vector(words[3], &tr.c))
		return (sc_err(line_num, "Bad format for triangle point coordinates"));
	tr.normal = cross(v_subtract(tr.b, tr.a), v_subtract(tr.c, tr.a));
	if (v_lenght(tr.normal) < EPSILON)
		return (sc_err(line_num, "Triangle points must not be aligned"));
	if (!parse_color(words[4], &obj.color))
		return (sc_err(line_num, "Bad format for triangle color"));
	obj.shine = TR_SHINE;
	if (!add_triangle(&scene->objects, obj, tr))
		return (0);
	return (1);
}

int	parse_cylinder(char **words, t_scene *scene, int line_num)
{
	t_obj		obj;
	t_cylinder	cyl;

	if (!check_n_words(words, line_num, 6))
		return (sc_err(line_num, "Too few arguments for cylinder"));
	if (!parse_vector(words[1], &cyl.center))
		return (sc_err(line_num, "Bad format for cylinder center"));
	if (!parse_vector(words[2], &cyl.dir))
		return (sc_err(line_num, "Bad format for cylinder orientation vector"));
	if (!check_orient_vector(cyl.dir))
		return (sc_err(line_num, "Bad values for cylinder orientation vector"));
	if (!parse_double(words[3], &cyl.radius))
		return (sc_err(line_num, "Bad format for cylinder diameter"));
	if (!parse_double(words[4], &cyl.height))
		return (sc_err(line_num, "Bad format for cylinder height"));
	cyl.radius /= 2;
	if (cyl.radius < 0 || cyl.height < 0)
		return (sc_err(line_num, "Cylinder diam & height must be positive"));
	if (!parse_color(words[5], &obj.color))
		return (sc_err(line_num, "Bad format for cylinder color"));
	obj.shine = CYL_SHINE;
	if (!add_cylinder(&scene->objects, obj, cyl))
		return (0);
	return (1);
}
