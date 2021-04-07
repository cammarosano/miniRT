/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:46:51 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:06:43 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*lst_next(t_list *lst_begin, t_list *current)
{
	if (current->next == NULL)
		return (lst_begin);
	return (current->next);
}

static t_list	*lst_prev(t_list *lst_begin, t_list *current)
{
	t_list	*ptr;

	if (current == lst_begin)
		return (ft_lstlast(lst_begin));
	ptr = lst_begin;
	while (ptr->next != NULL && ptr->next != current)
		ptr = ptr->next;
	return (ptr);
}

static void	switch_camera(int keycode, t_vars *vars)
{
	void	*img_ptr;

	if (keycode == KEY_N)
		vars->current_cam = lst_next(vars->scene->cameras,
				vars->current_cam);
	else
		vars->current_cam = lst_prev(vars->scene->cameras,
				vars->current_cam);
	img_ptr = ((t_camera *)vars->current_cam->content)->img_ptr;
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, img_ptr, 0, 0);
}

static void	move_camera(int keycode, t_vars *vars)
{
	t_camera	*cam;

	cam = vars->current_cam->content;
	if (keycode == KEY_W)
		cam->position = v_add((cam->position), v_scale(10, cam->dir));
	else if (keycode == KEY_S)
		cam->position = v_add((cam->position), v_scale(-10, cam->dir));
	else if (keycode == KEY_A)
		cam->position = v_add((cam->position), v_scale(-10, cam->u));
	else if (keycode == KEY_D)
		cam->position = v_add((cam->position), v_scale(10, cam->u));
	else if (keycode == KEY_UP)
		cam->position = v_add((cam->position), v_scale(10, cam->v));
	else if (keycode == KEY_DOWN)
		cam->position = v_add((cam->position), v_scale(-10, cam->v));
	ft_printf("New camera position: %.1f,%.1f,%.1f\n", cam->position.x,
		cam->position.y, cam->position.z);
	update_img(vars, cam);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_program(vars, 0);
	if (keycode == KEY_N || keycode == KEY_P)
		switch_camera(keycode, vars);
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_UP || keycode == KEY_DOWN)
		move_camera(keycode, vars);
	return (1);
}
