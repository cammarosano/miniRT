# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 13:39:16 by rcammaro          #+#    #+#              #
#    Updated: 2021/03/18 15:55:16 by rcammaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES		=	ft_printf.c \
				ft_utoa_base.c \
				ft_lltoa.c \
				ft_wchar_to_mb.c \
				parser.c \
				parser2.c \
				convert_char.c \
				convert_string.c \
				convert_integer.c \
				convert_pointer.c \
				convert_n.c \
				convert_float.c \
				convert_f.c \
				convert_e.c \
				convert_g.c \
				check_overflow.c \
				unknown_conversion.c \
				helpers.c \
				formating.c \
				formating2.c 

NAME		= 	libftprintf.a
CC			=	gcc
CFLAGS		= 	-Wall -Wextra -Werror
LIBFT		=	../libft_core/libft.a
SRC			=	$(addprefix srcs/,$(SOURCES))
OBJ			=	$(SRC:.c=.o)
HEADERS		=	includes/ft_printf_utils.h includes/ft_printf.h

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			cp $(LIBFT) $@
			ar -rcs $@ $(OBJ)

$(LIBFT):
			$(MAKE) -C ../libft_core

%.o:		%.c $(HEADERS) 
			$(CC) $(CFLAGS) -I./includes -o $@ -c $<

clean:
			$(MAKE) clean -C ../libft_core
			rm -f $(OBJ) 

fclean:		clean
			rm -f $(LIBFT)
			rm -f $(NAME)

re:			fclean all

bonus:		all

.PHONY:		all clean fclean re bonus
