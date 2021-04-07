/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercept_sph_cyl_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:30:52 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:16:11 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
** Solves for a.t^2 + b.t + c = 0
** Returns 1 if solutions exist, 0 otherwise.
** if a is positive, sol[0] stores the smallest solution
*/

static int		solve_2dg_equation(double a, double b, double c, double *sol)
{
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	sol[0] = (-b - sqrt(discriminant)) / (2 * a);
	sol[1] = (-b + sqrt(discriminant)) / (2 * a);
	return (1);
}

/*
** Returns the smallest solution greater than min, or +inf if no solution.
**
** sphere equation: (p - c) ^ 2 = r ^ 2 (p and c are points, r a scalar)
** line equation: p = o + t * dir (p and o are points, t a scalar, dir a vector)
** After solving for t, we get a.t^2 + b.t + c = 0 , in which:
** 		a = <direction,direction> (dot product)
** 		b = 2 . <CO,direction>
** 		c = <CO,CO> - r^2
*/

double			intercept_sphere(t_vect origin, t_vect direction, void *s,
									double min)
{
	t_vect	c_o;
	double	a;
	double	b;
	double	c;
	double	sol[2];

	c_o = v_subtract(origin, ((t_sphere *)s)->center);
	a = dot(direction, direction);
	b = 2 * dot(c_o, direction);
	c = dot(c_o, c_o) - ((t_sphere *)s)->radius * ((t_sphere *)s)->radius;
	if (!solve_2dg_equation(a, b, c, sol))
		return (1.0 / 0.0);
	if (sol[0] > min)
		return (sol[0]);
	if (sol[1] > min)
		return (sol[1]);
	return (1.0 / 0.0);
}

/*
** cylinder eq: [(P - cyl.center) x cyl.dir]^2 = cyl.radius^2 (x = cross prod)
** line eq: P = Po + t * line_dir
** "e" defined as Po - cyl.center
*/

static int		solve_inf_cyl(t_vect p0, t_vect line_d, t_cylinder cyl,
								double *sol)
{
	double	a;
	double	b;
	double	c;
	t_vect	ld_x_cd;
	t_vect	e_x_cd;

	ld_x_cd = cross(line_d, cyl.dir);
	e_x_cd = cross(v_subtract(p0, cyl.center), cyl.dir);
	a = dot(ld_x_cd, ld_x_cd);
	b = 2 * dot(ld_x_cd, e_x_cd);
	c = dot(e_x_cd, e_x_cd) - cyl.radius * cyl.radius;
	return (solve_2dg_equation(a, b, c, sol));
}

/*
** Checks the height (abs value), from the center of the cylinder, in which the
** point p occurs.
** line: p = p0 + t * dir
** cylinder center : c
*/

static double	interc_height(t_vect p0, double t, t_vect dir, t_cylinder cyl)
{
	t_vect	p;
	t_vect	cp;

	p = v_add(p0, v_scale(t, dir));
	cp = v_subtract(p, cyl.center);
	return (fabs(dot(cp, cyl.dir)));
}

/*
** Check for interceptions with a cylinder with infinite height. Then check if
** interception points lie between the height constraints.
*/

double			intercept_cylinder(t_vect origin, t_vect dir, void *shape,
									double min)
{
	double		half_height;
	double		inf;
	double		sol[2];
	t_cylinder	*cyl;

	cyl = shape;
	inf = 1.0 / 0.0;
	if (!solve_inf_cyl(origin, dir, *cyl, sol))
		return (inf);
	half_height = 0.5 * cyl->height;
	if (sol[0] > min && interc_height(origin, sol[0], dir, *cyl) < half_height)
		return (sol[0]);
	if (sol[1] > min && interc_height(origin, sol[1], dir, *cyl) < half_height)
		return (sol[1]);
	return (inf);
}
