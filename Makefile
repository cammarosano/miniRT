# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/18 22:08:52 by rcammaro          #+#    #+#              #
#    Updated: 2021/04/07 19:57:14 by rcammaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		add_cam_light_obj.c \
			add_primitives.c \
			bmp_image.c \
			clear_mem.c \
			color.c \
			interceptions_ray_obj.c \
			errors.c \
			hooks.c \
			hooks_2.c \
			images.c \
			intercept_pl_tr_sq.c \
			intercept_sph_cyl.c \
			linalg.c \
			linalg_2.c \
			main.c \
			normals.c \
			parse_cam_res_lights.c \
			parse_objects_2.c \
			parse_objects.c \
			parser.c \
			parser_switch.c \
			parser_utils.c \
			parser_utils_2.c \
			put_pixel_img.c \
			render.c \
			render_to_window.c \
			shading.c 

SRCS_B =	add_cam_light_obj_bonus.c \
			add_compound_obj_bonus.c \
			add_primitives_bonus.c \
			bmp_image_bonus.c \
			clear_mem_bonus.c \
			color_bonus.c \
			color_disruption_bonus.c \
			errors_bonus.c \
			hooks_2_bonus.c \
			hooks_bonus.c \
			images_bonus.c \
			interceptions_ray_obj_bonus.c \
			intercept_pl_tr_sq_bonus.c \
			intercept_sph_cyl_bonus.c \
			interc_norm_disc_bonus.c \
			linalg_2_bonus.c \
			linalg_bonus.c \
			main_bonus.c \
			normals_bonus.c \
			parse_cam_res_lights_bonus.c \
			parse_extras_bonus.c \
			parse_objects_2_bonus.c \
			parse_objects_bonus.c \
			parser_bonus.c \
			parser_switch_bonus.c \
			parser_utils_2_bonus.c \
			parser_utils_bonus.c \
			put_pixel_img_bonus.c \
			render_multithread_bonus.c \
			render_to_window_bonus.c \
			shading_bonus.c \
			single_sample_bonus.c \
			sky_bonus.c \
			supersampling_bonus.c

HEADERS = linalg.h  minirt.h  parser.h  primitives.h render.h
HEADERS_B = linalg_bonus.h  minirt_bonus.h  parser_bonus.h  \
			primitives_bonus.h  render_bonus.h
H_FILES = $(addprefix includes/,$(HEADERS)) \
			$(addprefix includes_bonus/,$(HEADERS_B))
 
SRC = $(addprefix srcs/,$(SRCS))
OBJ = $(SRC:.c=.o)
SRC_B = $(addprefix srcs_bonus/,$(SRCS_B))
OBJ_B = $(SRC_B:.c=.o)

CFLAGS = -Wall -Wextra -Werror
LIBS = -lft -L./libft -lmlx -L./minilibx-linux -lXext -lX11 -lm -pthread
INCLUDES = -I./includes -I./includes_bonus -I./libft -I./minilibx-linux -pthread

NAME = miniRT
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJ)
			$(CC) $(OBJ) $(LIBS) -o $@

$(MLX):
			$(MAKE) -C minilibx-linux

$(LIBFT):
			$(MAKE) all clean -C libft

%.o:		%.c $(H_FILES)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
			rm -f $(OBJ) $(OBJ_B)

fclean:		clean
			rm -f $(LIBFT)
			$(MAKE) clean -C minilibx-linux
			rm -f $(NAME)

re:			fclean all

bonus:		$(MLX) $(LIBFT) $(OBJ_B)
			$(CC) $(OBJ_B) $(LIBS) -o $(NAME)

.PHONY:		all clean fclean re bonus
