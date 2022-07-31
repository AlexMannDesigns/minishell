# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 13:44:30 by amann             #+#    #+#              #
#    Updated: 2022/07/26 13:02:19 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	FLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -O3 -D_DEFAULT_SOURCE
endif
ifeq ($(U_NAME_S), Darwin)
	FLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -O3
endif

LIB =  ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c	\
		ft_islower.c ft_lstiter.c ft_memcpy.c ft_memcmp.c ft_itoa.c ft_lstadd.c	\
		ft_lstdel.c ft_lstdelone.c ft_isprint.c	ft_lstmap.c ft_lstnew.c			\
		ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memdel.c ft_memmove.c			\
		ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_strcat.c		\
		ft_strequ.c ft_strmap.c ft_strmapi.c ft_putendl_fd.c ft_putnbr.c		\
		ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strchr.c ft_strclr.c		\
		ft_strcmp.c ft_strcpy.c	ft_strdel.c ft_strdup.c	ft_striter.c			\
		ft_striteri.c ft_strjoin.c ft_strlcat.c	ft_strlen.c ft_strncat.c		\
		ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strsplit.c		\
		ft_strstr.c ft_strsub.c	ft_strtrim.c ft_tolower.c ft_freearray.c		\
		ft_iswhitespace.c ft_abs.c ft_strnstr.c ft_strrchr.c ft_toupper.c		\
		ft_isupper.c ft_lstadd_back.c ft_strndup.c ft_itoa_base.c				\
		ft_itoa_base_unsigned.c	ft_abs_long.c ft_split_whitespace.c				\
		ft_array_len.c ft_print_array.c ft_is_dir.c ft_is_valid_path.c			\
		ft_string_insert.c
OBJ = $(LIB:.c=.o)
SRC_DIR = srcs/
LEAKS = -g -fsanitize=address

#rules
all: $(NAME)

$(NAME): 
	@gcc $(FLAGS) -c $(LIB)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
