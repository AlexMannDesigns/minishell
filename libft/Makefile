# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 11:48:22 by amann             #+#    #+#              #
#    Updated: 2022/09/01 14:41:04 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIB_FILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c			\
		ft_isdigit.c ft_islower.c ft_lstiter.c ft_memcpy.c ft_memcmp.c			\
		ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_isprint.c			\
		ft_lstmap.c ft_lstnew.c	ft_memalloc.c ft_memccpy.c ft_memchr.c			\
		ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c		\
		ft_putendl.c ft_strcat.c ft_strequ.c ft_strmap.c ft_strmapi.c			\
		ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c	\
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c	\
		ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c		\
		ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c			\
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c			\
		ft_free_array.c ft_iswhitespace.c ft_abs.c ft_strnstr.c ft_strrchr.c	\
		ft_toupper.c ft_abs_long.c ft_lstadd_back.c ft_strndup.c ft_isupper.c	\
		ft_itoa_base.c ft_itoa_base_unsigned.c ft_split_whitespace.c			\
		ft_array_len.c ft_print_array.c ft_is_dir.c ft_is_valid_path.c			\
		ft_string_insert.c
LIB_DIR = srcs/
LIB := $(patsubst %, $(LIB_DIR)/%, $(LIB_FILES)) 
LIB_OBJ = $(LIB:.c=.o)  

GNL_DIR	= get_next_line/
GNL = $(GNL_DIR)get_next_line.c $(GNL_DIR)gnl_helpers.c
GNL_OBJ = $(GNL:.c=.o)  

PRF_DIR = ft_printf/
PRF_FILES = conversion_control.c ft_printf.c set_flags.c print_result.c			\
		hash_flag.c flag_control.c numeric_conversion.c width_precision.c		\
		plus_flag.c handle_double.c add_sign.c ft_printf_putstr.c				\
		double_helpers.c double_helpers2.c signed_conversion_handlers.c			\
		unsigned_conversion_handlers.c n_conversion.c set_conv_type.c			\
		colours.c zero_flag.c chop_chop.c print_result_functions.c				\
		z_conversions.c ft_printf_control.c
PRF := $(patsubst %, $(PRF_DIR)/%, $(PRF_FILES)) 
PRF_OBJ = $(PRF:.c=.o)  

all: $(NAME)

$(NAME):
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) -C $(PRF_DIR)
	@ar rcs $(NAME) $(LIB_OBJ) $(GNL_OBJ) $(PRF_OBJ)
	@echo libft compiled

clean:
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@$(MAKE) -C $(PRF_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@$(MAKE) -C $(PRF_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
