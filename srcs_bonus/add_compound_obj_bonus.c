/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_compound_obj_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:57:59 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:23:02 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	add_6_squares(t_list **lst, t_obj obj, t_square *face)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!add_square(lst, obj, face[i]))
			return (0);
		i++;
	}
	return (1);
}

int	add_cube(t_list **lst, t_obj obj, t_square csq)
{
	t_square	face[6];
	int			i;

	face[0] = csq;
	face[2].normal = csq.u;
	face[2].u = csq.v;
	face[2].v = csq.normal;
	face[4].normal = csq.v;
	face[4].u = csq.u;
	face[4].v = csq.normal;
	i = 0;
	while (i < 6)
	{
		face[i].side = csq.side;
		if (i % 2)
		{
			face[i].normal = v_scale(-1, face[i - 1].normal);
			face[i].u = face[i - 1].u;
			face[i].v = face[i - 1].v;
		}
		face[i].center = v_add(csq.center,
				v_scale(csq.side / 2, face[i].normal));
		i++;
	}
	return (add_6_squares(lst, obj, face));
}

static void	get_base_points(t_square base, t_vect *vertex)
{
	t_vect	u;
	t_vect	v;
	int		i;

	u = v_scale(base.side / 2, base.u);
	v = v_scale(base.side / 2, base.v);
	vertex[0] = v_add(v_scale(-1, u), v_scale(-1, v));
	vertex[1] = v_add(u, v_scale(-1, v));
	vertex[2] = v_add(u, v);
	vertex[3] = v_add(v_scale(-1, u), v);
	i = -1;
	while (++i < 4)
		vertex[i] = v_add(vertex[i], base.center);
}

static t_triangle	get_triangle(t_vect *vertex, t_vect top, int i)
{
	t_triangle	tr;

	tr.a = vertex[i];
	tr.b = vertex[(i + 1) % 4];
	tr.c = top;
	tr.normal = cross(v_subtract(tr.b, tr.a), v_subtract(tr.c, tr.a));
	return (tr);
}

int	add_pyramid(t_list **lst, t_obj obj, t_square base, double height)
{
	t_vect		vertex[4];
	t_triangle	tr;
	t_vect		top;
	int			i;

	get_base_points(base, vertex);
	top = v_add(base.center, v_scale(height, base.normal));
	i = 0;
	while (i < 4)
	{
		tr = get_triangle(vertex, top, i);
		if (!add_triangle(lst, obj, tr))
			return (0);
		i++;
	}
	if (!add_square(lst, obj, base))
		return (0);
	return (1);
}
