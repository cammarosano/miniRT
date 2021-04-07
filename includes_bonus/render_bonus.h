/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:51:35 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 22:09:47 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

# include <pthread.h>
# include "parser_bonus.h"

# define AALIAS_THRSHD 0.05
# define N_THREADS 8
# define BOUNCES 3

typedef struct	s_img
{
	char		*addr;
	void		*img_ptr;
	int			bits_ppx;
	int			size_line;
	int			endian;
	int			height;
	int			width;
}				t_img;

typedef struct	s_hit_point
{
	t_vect		point;
	t_vect		surf_normal;
	t_vect		obj_color;
	int			shine;
	double		reflect;
}				t_hit_point;

typedef struct	s_m_thread_arg
{
	t_camera	*cam;
	t_scene		*scene;
	t_img		*img;
	void		(*put_pixel)(t_img *, int, int, int);
	int			y_init;
	int			y_end;
}				t_mthread_arg;

void			render(t_camera *camera, t_img *img, t_scene *scene,
						void (*put_pixel)(t_img *, int, int, int));
t_vect			single_sample(int x, int y, t_camera *cam, t_scene *scene);
t_vect			adapt_super_sample(int x, int y, t_camera *cam, t_scene *scene);
t_vect			calc_vector_dir(int x, int y, t_camera *cam, t_resol res);
t_vect			cast_ray(t_vect origin, t_vect dir, t_scene *scene,
							int bounces);

int				check_interception(t_vect origin, t_vect dir, t_list *obj_list,
									t_hit_point *hp);
double			intercept_obj(t_vect origin, t_vect direction, t_obj *obj,
								double min);
double			intercept_sphere(t_vect origin, t_vect direction, void *s,
									double min);
double			intercept_cylinder(t_vect origin, t_vect dir, void *shape,
									double min);
double			intercept_plane(t_vect origin, t_vect dir, void *shape,
								double min);
double			intercept_triangle(t_vect origin, t_vect dir, void *shape,
									double min);
double			intercept_square(t_vect origin, t_vect dir, void *shape,
									double min);
double			intercept_disc(t_vect origin, t_vect dir, void *shape,
								double min);

t_vect			normal_sphere(void *shape, t_vect point);
t_vect			normal_plane(void *shape, t_vect point);
t_vect			normal_triangle(void *shape, t_vect point);
t_vect			normal_square(void *shape, t_vect point);
t_vect			normal_cylinder(void *shape, t_vect point);
t_vect			normal_disc(void *shape, t_vect point);

t_vect			normal_disruption(t_vect normal, t_obj *obj, t_vect point);
int				checker_board(t_obj *obj, t_vect point);
t_vect			rainbow(t_vect normal);

t_vect			calc_shading(t_scene *scene, t_vect prim_ray,
								t_hit_point *point);
int				color_vtoi(t_vect color, int sepia);
t_vect			color_multiply(t_vect a, t_vect b);

t_vect			sky(t_vect ray, t_scene *scene);

#endif
