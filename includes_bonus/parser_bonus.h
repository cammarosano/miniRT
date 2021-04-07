/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:55:27 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 16:12:44 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "primitives_bonus.h"
# include "libft.h"

typedef struct	s_resol
{
	int			width;
	int			height;
	int			antialias;
}				t_resol;

typedef struct	s_camera
{
	t_vect		position;
	t_vect		dir;
	double		fov;
	int			sepia_filter;
	double		half_s;
	t_vect		u;
	t_vect		v;
	void		*img_ptr;
}				t_camera;

typedef	struct	s_light
{
	t_vect		pos_dir;
	t_vect		adj_color;
	int			type;
}				t_light;

enum			e_light_type
{
	spot,
	parallel
};

typedef struct	s_scene
{
	t_resol		res;
	t_vect		ambient;
	t_list		*lightspots;
	t_list		*objects;
	t_list		*cameras;
	int			sky;
}				t_scene;

int				parse_file(char *file_name, t_scene *scene);
int				parser_switch(char **words, t_scene *scene, int line_num);

int				parse_resolution(char **words, t_scene *scene, int line_num);
int				parse_ambient_light(char **words, t_scene *scene, int line_num);
int				parse_camera(char **words, t_scene *scene, int line_num);
int				parse_lightspot(char **words, t_scene *scene, int line_num);
int				parse_sphere(char **words, t_scene *scene, int line_num);
int				parse_plane(char **words, t_scene *scene, int line_num);
int				parse_square(char **words, t_scene *scene, int line_num);
int				parse_triangle(char **words, t_scene *scene, int line_num);
int				parse_cylinder(char **words, t_scene *scene, int line_num);
int				parse_cube(char **words, t_scene *scene, int line);
int				parse_pyramid(char **words, t_scene *scene, int line);
void			parse_extras(char **words, t_obj *obj);

int				count_split(char **words);
int				check_n_words(char **words, int line_num, int n_min);
int				check_file_extens(char *file_name);
int				parse_color(char *str, t_vect *color);
int				parse_vector(char *str, t_vect *v);
int				check_orient_vector(t_vect normal);
int				parse_double(char *str, double *nbr);
int				parse_int(char *str, int *nbr);

int				add_camera(t_list **list, t_camera src);
int				add_lightspot(t_list **list, t_vect pos_dir, t_vect adj_color,
								int type);
int				add_object(t_list **lst, t_obj *src_obj, size_t shape_size);
int				add_sphere(t_list **lst, t_obj obj, t_sphere sp);
int				add_plane(t_list **lst, t_obj obj, t_plane pl);
int				add_square(t_list **lst, t_obj obj, t_square sq);
int				add_triangle(t_list **lst, t_obj obj, t_triangle tr);
int				add_cylinder(t_list **lst, t_obj obj, t_cylinder cyl);
int				add_cube(t_list **lst, t_obj obj, t_square csq);
int				add_pyramid(t_list **lst, t_obj obj, t_square base,
							double height);

#endif
