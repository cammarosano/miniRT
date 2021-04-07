/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:08:38 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:44:18 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include "linalg.h"

typedef struct s_object
{
	int			type;
	t_vect		color;
	int			shine;
	void		*shape;
}				t_obj;

enum	e_object_types
{
	sphere = 0,
	plane,
	square,
	triangle,
	cylinder
};

typedef struct s_sphere
{
	t_vect		center;
	double		radius;
}				t_sphere;

typedef struct s_plane
{
	t_vect		point;
	t_vect		normal;
}				t_plane;

typedef struct s_triangle
{
	t_vect		a;
	t_vect		b;
	t_vect		c;
	t_vect		normal;
}				t_triangle;

typedef struct s_square
{
	t_vect		center;
	t_vect		normal;
	double		side;
	t_vect		u;
	t_vect		v;
}				t_square;

typedef struct s_cylinder
{
	t_vect		center;
	t_vect		dir;
	double		radius;
	double		height;
}				t_cylinder;

#endif
