/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cam_light_obj_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:56:51 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 17:48:55 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	add_lightspot(t_list **list, t_vect pos_dir, t_vect adj_color, int type)
{
	t_list	*node;
	t_light	*spot;

	spot = malloc(sizeof(*spot));
	if (!spot)
		return (0);
	spot->pos_dir = pos_dir;
	spot->adj_color = adj_color;
	spot->type = type;
	node = ft_lstnew(spot);
	if (!node)
	{
		free(spot);
		return (0);
	}
	ft_lstadd_front(list, node);
	return (1);
}

int	add_camera(t_list **list, t_camera src)
{
	t_list		*node;
	t_camera	*cam;

	cam = malloc(sizeof(*cam));
	if (!cam)
		return (0);
	cam->position = src.position;
	cam->dir = src.dir;
	cam->fov = src.fov;
	cam->sepia_filter = src.sepia_filter;
	cam->img_ptr = NULL;
	node = ft_lstnew(cam);
	if (!node)
	{
		free(cam);
		return (0);
	}
	ft_lstadd_back(list, node);
	return (1);
}

/*
** Duplicates the contents of src_obj and src_obj->shape to the heap and
** inserts the object to the front of list.
** Returns 1 upon success. If error, frees all allocated memory and returns 0.
*/

int	add_object(t_list **lst, t_obj *src_obj, size_t shape_size)
{
	t_obj	*obj;
	t_list	*new_node;

	obj = malloc(sizeof(*obj));
	if (!obj)
		return (0);
	ft_memcpy(obj, src_obj, sizeof(*obj));
	obj->shape = malloc(shape_size);
	if (!obj->shape)
	{
		free(obj);
		return (0);
	}
	ft_memcpy(obj->shape, src_obj->shape, shape_size);
	new_node = ft_lstnew(obj);
	if (!new_node)
	{
		free_object(obj);
		return (0);
	}
	ft_lstadd_front(lst, new_node);
	return (1);
}
