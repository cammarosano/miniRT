/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_primitives_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:56:17 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 14:25:16 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	add_sphere(t_list **lst, t_obj obj, t_sphere sp)
{
	obj.type = sphere;
	obj.shape = &sp;
	if (!add_object(lst, &obj, sizeof(sp)))
		return (0);
	return (1);
}

int	add_plane(t_list **lst, t_obj obj, t_plane pl)
{
	obj.type = plane;
	obj.shape = &pl;
	if (!add_object(lst, &obj, sizeof(pl)))
		return (0);
	return (1);
}

int	add_square(t_list **lst, t_obj obj, t_square sq)
{
	obj.type = square;
	obj.shape = &sq;
	if (!add_object(lst, &obj, sizeof(sq)))
		return (0);
	return (1);
}

int	add_triangle(t_list **lst, t_obj obj, t_triangle tr)
{
	obj.type = triangle;
	obj.shape = &tr;
	tr.normal = v_normalize(tr.normal);
	if (!add_object(lst, &obj, sizeof(tr)))
		return (0);
	return (1);
}

int	add_cylinder(t_list **lst, t_obj obj, t_cylinder cyl)
{
	t_disc	ds;

	obj.type = cylinder;
	obj.shape = &cyl;
	cyl.dir = v_normalize(cyl.dir);
	if (!add_object(lst, &obj, sizeof(cyl)))
		return (0);
	if (obj.cyl_caps)
	{
		obj.type = disc;
		obj.shape = &ds;
		ds.center = v_add(cyl.center, v_scale(cyl.height / 2, cyl.dir));
		ds.normal = cyl.dir;
		ds.radius = cyl.radius;
		if (!add_object(lst, &obj, sizeof(ds)))
			return (0);
		ds.center = v_add(cyl.center, v_scale(-cyl.height / 2, cyl.dir));
		if (!add_object(lst, &obj, sizeof(ds)))
			return (0);
	}
	return (1);
}
