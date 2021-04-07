/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cam_light_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:56:51 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 17:53:17 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_lightspot(t_list **list, t_vect position, t_vect adj_color)
{
	t_list	*node;
	t_spot	*spot;

	spot = malloc(sizeof(*spot));
	if (!spot)
		return (0);
	spot->position = position;
	spot->adj_color = adj_color;
	node = ft_lstnew(spot);
	if (!node)
	{
		free(spot);
		return (0);
	}
	ft_lstadd_front(list, node);
	return (1);
}

int	add_camera(t_list **list, t_vect position, t_vect dir, double fov)
{
	t_list		*node;
	t_camera	*cam;

	cam = malloc(sizeof(*cam));
	if (!cam)
		return (0);
	cam->position = position;
	cam->dir = dir;
	cam->fov = fov;
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
