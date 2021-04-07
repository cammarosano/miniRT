/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:37:26 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 20:13:20 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
** Parses line by spliting in into words, using any whitespace as separator,
** and calls the suitable function via parser_switch.
** Returns 1 upon success (or if line is the empty string), 0 if error.
*/

static int	parse_line(char *line, t_scene *scene, int line_num)
{
	char	**words;
	int		ret;

	if (!*line)
		return (1);
	words = ft_split_charset(line, " \t\v\f\r");
	if (!words)
		return (syscall_err("ft_split_charset()"));
	if (!words[0])
		return (1);
	ret = parser_switch(words, scene, line_num);
	ft_free_split(words);
	if (!ret)
		return (0);
	return (1);
}

static int	parse_scene(int fd, t_scene *scene)
{
	char	*line;
	int		ret;
	int		line_num;

	line_num = 0;
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		ret = parse_line(line, scene, ++line_num);
		free(line);
		if (!ret)
			return (0);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (syscall_err("get_next_line()"));
	ret = parse_line(line, scene, ++line_num);
	free(line);
	if (!ret)
		return (0);
	return (1);
}

/*
** The -1 value is used to signal that the element (ambient lighting and
** resolution) has not yet been parsed from the scene file.
*/

static void	initialize_scene(t_scene *scene)
{
	scene->ambient.x = -1.0;
	scene->res.width = -1;
	scene->cameras = NULL;
	scene->lightspots = NULL;
	scene->objects = NULL;
	scene->sky = 0;
}

static int	validate_scene(t_scene *scene)
{
	if (scene->ambient.x < 0)
		return (sc_err(0, "Ambient lighting missing"));
	if (scene->res.width < 0)
		return (sc_err(0, "Resolution missing"));
	if (!scene->cameras)
		return (sc_err(0, "At least one camera is required"));
	if (!scene->objects)
		sc_warning(0, "No objects");
	return (1);
}

int	parse_file(char *file_name, t_scene *scene)
{
	int		fd;
	int		ret;

	if (!check_file_extens(file_name))
		return (0);
	initialize_scene(scene);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (syscall_err("open()"));
	ret = parse_scene(fd, scene);
	close(fd);
	if (!ret || !validate_scene(scene))
	{
		clear_scene_lists(scene);
		return (0);
	}
	return (1);
}
