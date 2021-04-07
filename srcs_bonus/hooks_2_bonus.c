/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:09:15 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:36:20 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	red_cross(t_vars *vars)
{
	close_program(vars, 0);
	return (1);
}

void	update_img(t_vars *vars, t_camera *cam)
{
	t_img	img;

	if (!render_img(&img, cam, vars->scene, vars->mlx_ptr))
		close_program(vars, 1);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, img.img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx_ptr, cam->img_ptr);
	cam->img_ptr = img.img_ptr;
}

static void	cam_rotation_mouse(int x, int y, t_vars *vars)
{
	t_camera	*cam;
	t_vect		new_dir;

	cam = vars->current_cam->content;
	new_dir = calc_vector_dir(x, y, cam, vars->scene->res);
	cam->dir = new_dir;
	ft_printf("New camera orientation: %.1f,%.1f,%.1f\n", new_dir.x, new_dir.y,
		new_dir.z);
	update_img(vars, cam);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	if (button == 3)
		cam_rotation_mouse(x, y, vars);
	return (1);
}

int	keep_win_alive(t_vars *vars)
{
	void	*img_ptr;

	img_ptr = ((t_camera *)vars->current_cam->content)->img_ptr;
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, img_ptr, 0, 0);
	return (1);
}
