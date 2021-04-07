/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:41:43 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 18:36:55 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int			render_to_bmp(int argc, char **argv)
{
	t_scene	scene;
	t_img	img;
	int		ret;
	char	*bmp_file;

	if (!parse_file(argv[1], &scene))
		return (0);
	if (!new_bmp_img(&img, scene.res.width, scene.res.height))
	{
		clear_scene_lists(&scene);
		return (0);
	}
	ft_putstr_fd("Rendering image... ", 1);
	render(scene.cameras->content, &img, &scene, put_pixel_bmp);
	ft_putendl_fd("done.", 1);
	bmp_file = "out.bmp";
	if (argc > 3)
		bmp_file = argv[3];
	ret = img_2_bmp_file(&img, bmp_file);
	clear_scene_lists(&scene);
	free(img.addr);
	return (ret);
}

static int	print_help(void)
{
	ft_printf("Bonus parameters:\n");
	ft_printf("(add after positional arguments in .rt file)\n");
	ft_printf("--anti-aliasing to R (resolution)\n");
	ft_printf("--blue-sky to A (ambient)\n");
	ft_printf("--night-sky to A (ambient)\n");
	ft_printf("--sepia to c (camera)\n");
	ft_printf("--parallel to l (inform orientation instead of position)\n");
	ft_printf("-r [0.0,1.0] to any object (reflection)\n");
	ft_printf("-s [1,1000] to any object (specular shine)\n");
	ft_printf("--caps to cy (cylinder)\n");
	ft_printf("-nd [wave lenght] to pl or sq (normal disruption)\n");
	ft_printf("-cb [size] to pl or sq (color disruption: checkerboard)\n");
	ft_printf("--rainbow to any object (color disruption: rainbow effect)\n");
	return (0);
}

int			main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putendl_fd("Usage: ./miniRT SCENE.rt [--save [FILE]]", 2);
		ft_putendl_fd("       ./miniRT --help", 2);
		return (1);
	}
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "--help") == 0)
			return (print_help());
		render_to_window(argv[1]);
	}
	if (ft_strcmp(argv[2], "--save") != 0)
	{
		ft_putstr_fd("Error\nInvalid argument: ", 2);
		ft_putendl_fd(argv[2], 2);
		return (1);
	}
	if (!render_to_bmp(argc, argv))
		return (1);
	return (0);
}
