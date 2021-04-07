/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:34:21 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:02:32 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	word_to_index(char *word, char *types)
{
	int		index;
	char	id[3];
	int		i;

	index = 0;
	while (*types)
	{
		i = 0;
		while (ft_isalpha(*types))
			id[i++] = *types++;
		id[i] = '\0';
		if (!ft_strcmp(word, id))
			return (index);
		while (*types == ' ')
			types++;
		index++;
	}
	return (-1);
}

int	parser_switch(char **words, t_scene *scene, int line_num)
{
	int			index;
	static	int	(*func[10])(char **, t_scene *, int) = {parse_resolution,
	parse_ambient_light, parse_camera, parse_lightspot, parse_sphere,
	parse_plane, parse_square, parse_triangle, parse_cylinder};

	index = word_to_index(words[0], "R A c l sp pl sq tr cy");
	if (index == -1)
		return (sc_err(line_num, "Unknown type identifier"));
	return (func[index](words, scene, line_num));
}
