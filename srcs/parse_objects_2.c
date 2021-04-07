/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:32:10 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:17:06 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	parse_square(char **words, t_scene *scene, int line_num)
{
	t_obj		obj;
	t_square	sq;

	if (!check_n_words(words, line_num, 5))
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
	obj.shine = SQ_SHINE;
	load_uv_coords_sq(&sq);
	if (!add_square(&scene->objects, obj, sq))
		return (0);
	return (1);
}
