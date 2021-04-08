/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:41:04 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/08 13:56:26 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "render.h"
# include "stdio.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define EPSILON 1.0e-10

# define KEY_ESC 0xff1b
# define KEY_N 0x006e
# define KEY_P 0x0070
# define KEY_W 0x0077
# define KEY_S 0x0073
# define KEY_A 0x0061
# define KEY_D 0x0064
# define KEY_UP 0xff52
# define KEY_DOWN 0xff54

typedef struct s_vars
{
	t_scene	*scene;
	void	*win_ptr;
	void	*mlx_ptr;
	t_list	*current_cam;
}				t_vars;

void	render_to_window(char *file_name);
void	adjust_res_2_screen(void *mlx_ptr, t_resol *res);
int		render_img(t_img *img, t_camera *cam, t_scene *scene, void *mlx_ptr);
int		render_all_cams(void *first_img_ptr, t_scene *scene, void *mlx_ptr);

int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int button, int x, int y, t_vars *vars);
int		red_cross(t_vars *vars);
void	update_img(t_vars *vars, t_camera *cam);
int		keep_win_alive(t_vars *vars);

int		img_2_bmp_file(t_img *img, char *file);
int		new_bmp_img(t_img *img, int width, int height);

void	put_pixel_mlx_le(t_img *img, int x, int y, int color);
void	put_pixel_mlx_be(t_img *img, int x, int y, int color);
void	put_pixel_bmp(t_img *img, int x, int y, int color);

int		sc_err(int line_num, char *msg);
int		syscall_err(char *function_name);
void	sc_warning(int line_num, char *msg);

void	free_object(void *obj);
void	clear_scene_lists(t_scene *scene);
int		close_program(t_vars *vars, int exit_code);

#endif
