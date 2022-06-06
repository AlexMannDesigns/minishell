# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 12:13:10 by amann             #+#    #+#              #
#    Updated: 2022/03/19 18:08:22 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror -ansi -pedantic -std=c99 -O3
SRCS = conversion_control.c ft_printf.c	set_flags.c print_result.c hash_flag.c	\
		flag_control.c numeric_conversion.c width_precision.c plus_flag.c		\
		handle_double.c ft_printf_putstr.c double_helpers.c	double_helpers2.c	\
		signed_conversion_handlers.c unsigned_conversion_handlers.c add_sign.c	\
		n_conversion.c set_conv_type.c colours.c ft_printf_control.c			\
		chop_chop.c print_result_functions.c zero_flag.c z_conversions.c
OBJ = $(SRCS:.c=.o)
LEAKS = -g -fsanitize=address

all:
	@gcc $(FLAGS) -c $(SRCS)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
