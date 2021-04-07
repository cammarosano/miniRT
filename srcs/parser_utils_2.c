/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 01:36:13 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 18:09:37 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_orient_vector(t_vect normal)
{
	if (fabs(normal.x) > 1 || fabs(normal.y) > 1 || fabs(normal.z) > 1)
		return (0);
	if (v_lenght(normal) < EPSILON)
		return (0);
	return (1);
}

static int	count_split(char **words)
{
	int	i;

	if (!words)
		return (-1);
	i = 0;
	while (*words++)
		i++;
	return (i);
}

int	check_n_words(char **words, int line_num, int expected_n)
{
	int	n;

	n = count_split(words);
	if (n < expected_n)
		return (0);
	if (n > expected_n)
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
