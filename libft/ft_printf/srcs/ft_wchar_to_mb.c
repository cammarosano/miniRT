/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_mb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:05:11 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 15:27:00 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/*
** Layout of UTF-8 byte sequences
** n	First 		Last 		Byte 1		Byte 2		Byte 3		Byte 4
** 1	U+0000		U+007F		0xxxxxxx
** 2	U+0080		U+07FF		110xxxxx	10xxxxxx
** 3	U+0800		U+FFFF		1110xxxx	10xxxxxx	10xxxxxx
** 4	U+10000		U+10FFFF	11110xxx	10xxxxxx	10xxxxxx	10xxxxxx
*/

static int	wchar_to_mb_part_2(char *buffer, wchar_t code_point)
{
	if (code_point <= 0xffff)
	{
		buffer[2] = 0b10000000 | (code_point & 0b111111);
		buffer[1] = 0b10000000 | ((code_point >> 6) & 0b111111);
		buffer[0] = 0b11100000 | (code_point >> 12);
		return (3);
	}
	if (code_point <= 0x10ffff)
	{
		buffer[3] = 0b10000000 | (code_point & 0b111111);
		buffer[2] = 0b10000000 | ((code_point >> 6) & 0b111111);
		buffer[1] = 0b10000000 | ((code_point >> 12) & 0b111111);
		buffer[0] = 0b11110000 | (code_point >> 18);
		return (4);
	}
	return (0);
}

int	ft_wchar_to_mb(char *buffer, wchar_t code_point)
{
	if (code_point < 0)
		return (0);
	if (code_point <= 0x007f)
	{
		buffer[0] = code_point;
		return (1);
	}
	if (code_point <= 0x07ff)
	{
		buffer[1] = 0b10000000 | (code_point & 0b111111);
		buffer[0] = 0b11000000 | (code_point >> 6);
		return (2);
	}
	return (wchar_to_mb_part_2(buffer, code_point));
}
