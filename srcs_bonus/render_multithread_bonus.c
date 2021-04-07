/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_multithread_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:06:00 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:23:46 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	*render_block(void *arg)
{
	t_mthread_arg	*v;
	int				x;
	int				y;
	t_vect			color;
	static	t_vect	(*sampling[2])(int, int, t_camera *, t_scene *) = {
				single_sample, adapt_super_sample};

	v = arg;
	y = v->y_init;
	while (y < v->y_end)
	{
		x = 0;
		while (x < v->scene->res.width)
		{
			color = sampling[v->scene->res.antialias](x, y, v->cam, v->scene);
			v->put_pixel(v->img, x, y, color_vtoi(color, v->cam->sepia_filter));
			x++;
		}
		y++;
	}
	return (NULL);
}

static void	replicate_args_array(t_mthread_arg *v, int step)
{
	int	i;

	i = 1;
	while (i < N_THREADS)
	{
		ft_memcpy(&v[i], &v[i - 1], sizeof(v[i]));
		v[i].y_init = v[i].y_end;
		v[i].y_end += step;
		i++;
	}
}

/*
** scale_factor = 2 * tan(fov/2) / res.width
** One unit in pixel coordinates correspondes to scale_fator in the view pane,
** which is located 1 unit away (scene coordinates) from the camera position.
** half_s stores half of the scale_factor.
*/

static void	setup_cam(t_camera *cam, t_resol res)
{
	t_vect	up;
	t_vect	u;
	t_vect	v;
	t_vect	w;

	up = vector(0, 1, 0);
	w = v_normalize(cam->dir);
	u = cross(w, up);
	if (v_lenght(u) < 1.0e-50)
		u = vector(1, 0, 0);
	v = cross(u, w);
	cam->dir = w;
	cam->u = v_normalize(u);
	cam->v = v_normalize(v);
	cam->half_s = tan(deg_to_rad(cam->fov) * 0.5) / res.width;
}

void	render(t_camera *camera, t_img *img, t_scene *scene,
				void (*put_pixel)(t_img *, int, int, int))
{
	pthread_t		thread_ids[N_THREADS];
	t_mthread_arg	v[N_THREADS];
	int				step;
	int				i;

	setup_cam(camera, scene->res);
	step = scene->res.height / N_THREADS;
	v[0].cam = camera;
	v[0].img = img;
	v[0].scene = scene;
	v[0].put_pixel = put_pixel;
	v[0].y_init = 0;
	v[0].y_end = step;
	replicate_args_array(v, step);
	i = 0;
	while (++i < N_THREADS)
		pthread_create(&thread_ids[i], NULL, render_block, &v[i]);
	render_block(&v[0]);
	i = 0;
	while (++i < N_THREADS)
		pthread_join(thread_ids[i], NULL);
}
