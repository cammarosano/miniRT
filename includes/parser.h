/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:04:40 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:43:42 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "primitives.h"
# include "libft.h"

# define SP_SHINE 800
# define PL_SHINE 4
# define SQ_SHINE 50
# define TR_SHINE 50
# define CYL_SHINE 50

typedef struct s_resol
{
	int			width;
	int			height;
}				t_resol;

typedef struct s_camera
{
	t_vect		position;
	t_vect		dir;
	double		fov;
	double		half_s;
	t_vect		u;
	t_vect		v;
	void		*img_ptr;
}				t_camera;

typedef struct s_spot
{
	t_vect		position;
	t_vect		adj_color;
}				t_spot;

typedef struct s_scene
{
	t_resol		res;
	t_vect		ambient;
	t_list		*lightspots;
	t_list		*objects;
	t_list		*cameras;
}				t_scene;

int	parse_file(char *file_name, t_scene *scene);
int	parser_switch(char **words, t_scene *scene, int line_num);

int	parse_resolution(char **words, t_scene *scene, int line_num);
int	parse_ambient_light(char **words, t_scene *scene, int line_num);
int	parse_camera(char **words, t_scene *scene, int line_num);
int	parse_lightspot(char **words, t_scene *scene, int line_num);
int	parse_sphere(char **words, t_scene *scene, int line_num);
int	parse_plane(char **words, t_scene *scene, int line_num);
int	parse_square(char **words, t_scene *scene, int line_num);
int	parse_triangle(char **words, t_scene *scene, int line_num);
int	parse_cylinder(char **words, t_scene *scene, int line_num);

int	check_file_extens(char *file_name);
int	check_n_words(char **words, int line_num, int expected_n);
int	parse_color(char *str, t_vect *color);
int	parse_vector(char *str, t_vect *v);
int	check_orient_vector(t_vect normal);
int	parse_double(char *str, double *nbr);
int	parse_int(char *str, int *nbr);

int	add_camera(t_list **list, t_vect position, t_vect dir, double fov);
int	add_lightspot(t_list **list, t_vect position, t_vect adj_color);
int	add_object(t_list **lst, t_obj *src_obj, size_t shape_size);
int	add_sphere(t_list **lst, t_obj obj, t_sphere sp);
int	add_plane(t_list **lst, t_obj obj, t_plane pl);
int	add_square(t_list **lst, t_obj obj, t_square sq);
int	add_triangle(t_list **lst, t_obj obj, t_triangle tr);
int	add_cylinder(t_list **lst, t_obj obj, t_cylinder cyl);

#endif
