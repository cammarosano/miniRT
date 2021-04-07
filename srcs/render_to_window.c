/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_to_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:55:22 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:19:52 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	connect_mlx(t_vars *vars)
{
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
	{
		ft_putendl_fd(
			"mlx_init() error: failed to set up connection to X server", 2);
		clear_scene_lists(vars->scene);
		exit(1);
	}
}

static void	initialize_vars(t_vars *vars, t_scene *scene)
{
	vars->scene = scene;
	vars->win_ptr = NULL;
	vars->current_cam = scene->cameras;
}

static void	create_window(t_vars *vars, t_resol res)
{
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, res.width, res.height,
			"miniRT");
	if (!vars->win_ptr)
	{
		ft_putendl_fd(
			"mlx_new_window() error: failed to create new window", 2);
		close_program(vars, 1);
	}
}

void	display_instructions(void)
{
	ft_putendl_fd("Interaction with the image window:", 1);
	ft_putendl_fd("Press keys N and P to select next/previous camera", 1);
	ft_putendl_fd("Press keys W, S, A, D and arrows UP/DOWN to move camera", 1);
	ft_putendl_fd("Mouse: point and right click to rotate camera", 1);
}

void	render_to_window(char *file_name)
{
	t_scene	scene;
	t_vars	vars;
	t_img	first_img;

	if (!parse_file(file_name, &scene))
		exit(1);
	initialize_vars(&vars, &scene);
	connect_mlx(&vars);
	adjust_res_2_screen(vars.mlx_ptr, &scene.res);
	if (!render_img(&first_img, scene.cameras->content, &scene, vars.mlx_ptr))
		close_program(&vars, 1);
	create_window(&vars, scene.res);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, first_img.img_ptr,
		0, 0);
	if (!render_all_cams(first_img.img_ptr, &scene, vars.mlx_ptr))
		close_program(&vars, 1);
	mlx_hook(vars.win_ptr, 33, (1L << 17), red_cross, &vars);
	mlx_key_hook(vars.win_ptr, key_hook, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx_ptr, keep_win_alive, &vars);
	display_instructions();
	mlx_loop(vars.mlx_ptr);
}
