/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:37 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:41:55 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINALG_H
# define LINALG_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vect;

double			dot(t_vect v, t_vect w);
t_vect			cross(t_vect v, t_vect w);
t_vect			v_scale(double k, t_vect v);
double			v_lenght(t_vect v);
t_vect			v_subtract(t_vect dest, t_vect origin);
t_vect			v_add(t_vect v, t_vect w);
t_vect			v_normalize(t_vect v);
t_vect			vector(double x, double y, double z);
t_vect			reflected(t_vect v, t_vect normal);
double			deg_to_rad(double angle_deg);

#endif
