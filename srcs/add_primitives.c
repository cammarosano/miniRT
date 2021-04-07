/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_primitives.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:56:17 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 17:07:00 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	pl.normal = v_normalize(pl.normal);
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
	obj.type = cylinder;
	obj.shape = &cyl;
	cyl.dir = v_normalize(cyl.dir);
	if (!add_object(lst, &obj, sizeof(cyl)))
		return (0);
	return (1);
}
