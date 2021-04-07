/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:36:13 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/29 18:05:54 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_orient_vector(t_vect normal)
{
	if (fabs(normal.x) > 1 || fabs(normal.y) > 1 || fabs(normal.z) > 1)
		return (0);
	if (v_lenght(normal) < EPSILON)
		return (0);
	return (1);
}

int	count_split(char **words)
{
	int	i;

	if (!words)
		return (-1);
	i = 0;
	while (*words++)
		i++;
	return (i);
}

int	check_n_words(char **words, int line_num, int n_min)
{
	int	n;

	n = count_split(words);
	if (n < n_min)
		return (0);
	if (n > n_min)
		sc_warning(line_num, "extra arguments will be ignored");
	return (1);
}

int	check_file_extens(char *file_name)
{
	char	*ptr;

	if (ft_strlen(file_name) >= 3)
	{
		ptr = file_name;
		while (*ptr)
			ptr++;
		ptr = ptr - 3;
		if (ft_strcmp(ptr, ".rt") == 0)
			return (1);
	}
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("Scene description file name must have .rt extension ", 2);
	return (0);
}
