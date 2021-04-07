/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_image_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:12:27 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 17:33:42 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
** Allocates memory for the raw pixel data section of a 24 bits per pixel
** bitmap file and sets the atributes of img accordingly.
*/

int	new_bmp_img(t_img *img, int width, int height)
{
	int	padding;

	padding = (4 - (width * 3) % 4) % 4;
	img->size_line = width * 3 + padding;
	img->addr = ft_calloc(height * img->size_line, 1);
	if (!img->addr)
		return (syscall_err("ft_calloc"));
	img->bits_ppx = 24;
	img->endian = 0;
	img->height = height;
	img->width = width;
	return (1);
}

static void	int2char_little_endian(int nbr, unsigned char *ptr)
{
	ptr[0] = (unsigned char)nbr;
	ptr[1] = (unsigned char)(nbr >> 8);
	ptr[2] = (unsigned char)(nbr >> 16);
	ptr[3] = (unsigned char)(nbr >> 24);
}

static void	bmp_file_header(int fd, int px_data_size)
{
	unsigned char	fheader[14];
	int				file_size;

	file_size = 14 + 40 + px_data_size;
	ft_bzero(fheader, 14);
	fheader[0] = 'B';
	fheader[1] = 'M';
	int2char_little_endian(file_size, fheader + 2);
	fheader[10] = 54;
	write(fd, fheader, 14);
}

static void	bmp_info_header(int fd, int width, int height)
{
	unsigned char	iheader[40];

	ft_bzero(iheader, 40);
	iheader[0] = 40;
	int2char_little_endian(width, iheader + 4);
	int2char_little_endian(height, iheader + 8);
	iheader[12] = 1;
	iheader[14] = 24;
	write(fd, iheader, 40);
}

int	img_2_bmp_file(t_img *img, char *file)
{
	int	fd;
	int	px_data_size;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (syscall_err("open()"));
	if (write(fd, "", 0) == -1)
	{
		close(fd);
		return (syscall_err("write()"));
	}
	px_data_size = img->height * img->size_line;
	bmp_file_header(fd, px_data_size);
	bmp_info_header(fd, img->width, img->height);
	write(fd, img->addr, px_data_size);
	ft_printf("Image saved as %s\n", file);
	close(fd);
	return (1);
}
