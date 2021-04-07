/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:04:15 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 17:48:11 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_object(void *obj)
{
	free(((t_obj *)obj)->shape);
	free(obj);
}

void	clear_scene_lists(t_scene *scene)
{
	ft_lstclear(&scene->cameras, free);
	ft_lstclear(&scene->lightspots, free);
	ft_lstclear(&scene->objects, free_object);
}

static void	clear_images(t_list *cam_lst, void *mlx_ptr)
{
	t_camera	*cam;

	while (cam_lst)
	{
		cam = cam_lst->content;
		if (cam && cam->img_ptr)
			mlx_destroy_image(mlx_ptr, cam->img_ptr);
		cam_lst = cam_lst->next;
	}
}

int	close_program(t_vars *vars, int exit_code)
{
	if (vars->win_ptr)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	clear_images(vars->scene->cameras, vars->mlx_ptr);
	clear_scene_lists(vars->scene);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	exit(exit_code);
}
