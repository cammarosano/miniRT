/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:23:03 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:08:41 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	adjust_res_2_screen(void *mlx_ptr, t_resol *res)
{
	int	size_x;
	int	size_y;

	mlx_get_screen_size(mlx_ptr, &size_x, &size_y);
	if (res->width > size_x)
		res->width = size_x;
	if (res->height > size_y)
		res->height = size_y;
}

/*
** Creates a new image and renders the scene for the specified camera.
** Returns 0 if failed to create new image, 1 upon success.
*/

int	render_img(t_img *img, t_camera *cam, t_scene *scene, void *mlx_ptr)
{
	void	(*put_pixel)(t_img *, int, int, int);

	img->img_ptr = mlx_new_image(mlx_ptr, scene->res.width, scene->res.height);
	if (!img->img_ptr)
	{
		ft_putendl_fd("mlx_new_image() error: failed to create new image", 2);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_ppx,
			&img->size_line, &img->endian);
	put_pixel = put_pixel_mlx_le;
	if (img->endian)
		put_pixel = put_pixel_mlx_be;
	ft_putstr_fd("Rendering image... ", 1);
	render(cam, img, scene, put_pixel);
	ft_putendl_fd("done.", 1);
	return (1);
}

int	render_all_cams(void *first_img_ptr, t_scene *scene, void *mlx_ptr)
{
	t_list		*list;
	t_camera	*cam;
	t_img		img;

	list = scene->cameras;
	cam = list->content;
	cam->img_ptr = first_img_ptr;
	list = list->next;
	while (list)
	{
		cam = list->content;
		if (!render_img(&img, cam, scene, mlx_ptr))
			return (0);
		cam->img_ptr = img.img_ptr;
		list = list->next;
	}
	return (1);
}
