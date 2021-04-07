/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:05:15 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 14:33:06 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	parse_shine(char **words, t_obj *obj)
{
	int	shine;

	if (!*++words)
		return ;
	shine = ft_atoi(*words);
	if (shine < 1)
		shine = 1;
	obj->shine = shine;
}

static void	parse_reflect(char **words, t_obj *obj)
{
	double	reflect;

	if (!*++words)
		return ;
	reflect = ft_atof(*words);
	if (reflect < 0)
		reflect = 0;
	if (reflect > 1)
		reflect = 1;
	obj->reflect = reflect;
}

static void	set_defaults(t_obj *obj)
{
	obj->shine = 1;
	obj->reflect = 0.0;
	obj->cyl_caps = 0;
	obj->n_disrup_wlen = 0;
	obj->checker_size = 0;
	obj->rainbow = 0;
}

void		parse_extras(char **words, t_obj *obj)
{
	set_defaults(obj);
	while (*words && **words != '#')
	{
		if (!ft_strcmp(*words, "-s"))
			parse_shine(words, obj);
		else if (!ft_strcmp(*words, "-r"))
			parse_reflect(words, obj);
		else if (!ft_strcmp(*words, "--caps"))
			obj->cyl_caps = 1;
		else if (!ft_strcmp(*words, "-nd") && words[1])
			obj->n_disrup_wlen = ft_atof(words[1]);
		else if (!ft_strcmp(*words, "-cb") && words[1])
			obj->checker_size = ft_atof(words[1]);
		else if (!ft_strcmp(*words, "--rainbow"))
			obj->rainbow = 1;
		words++;
	}
}
