# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 11:48:22 by amann             #+#    #+#              #
#    Updated: 2022/09/01 13:05:36 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIB_DIR = srcs/
GNL_DIR	= get_next_line/
PRF_DIR = ft_printf/
LIB_DIR = srcs/
GNL_DIR	= get_next_line/
PRF_DIR = ft_printf/
LIB = $(LIB_DIR)ft_atoi.c $(LIB_DIR)ft_bzero.c $(LIB_DIR)ft_isalnum.c			\
		$(LIB_DIR)ft_isalpha.c $(LIB_DIR)ft_isascii.c $(LIB_DIR)ft_isdigit.c	\
		$(LIB_DIR)ft_islower.c $(LIB_DIR)ft_lstiter.c $(LIB_DIR)ft_memcpy.c		\
		$(LIB_DIR)ft_memcmp.c $(LIB_DIR)ft_itoa.c $(LIB_DIR)ft_lstadd.c			\
		$(LIB_DIR)ft_lstdel.c $(LIB_DIR)ft_lstdelone.c $(LIB_DIR)ft_isprint.c	\
		$(LIB_DIR)ft_lstmap.c $(LIB_DIR)ft_lstnew.c	$(LIB_DIR)ft_memalloc.c		\
		$(LIB_DIR)ft_memccpy.c $(LIB_DIR)ft_memchr.c $(LIB_DIR)ft_memdel.c		\
		$(LIB_DIR)ft_memmove.c $(LIB_DIR)ft_memset.c $(LIB_DIR)ft_putchar.c		\
		$(LIB_DIR)ft_putchar_fd.c $(LIB_DIR)ft_putendl.c $(LIB_DIR)ft_strcat.c	\
		$(LIB_DIR)ft_strequ.c $(LIB_DIR)ft_strmap.c $(LIB_DIR)ft_strmapi.c		\
		$(LIB_DIR)ft_putendl_fd.c $(LIB_DIR)ft_putnbr.c $(LIB_DIR)ft_putnbr_fd.c\
		$(LIB_DIR)ft_putstr.c $(LIB_DIR)ft_putstr_fd.c $(LIB_DIR)ft_strchr.c	\
		$(LIB_DIR)ft_strclr.c $(LIB_DIR)ft_strcmp.c $(LIB_DIR)ft_strcpy.c		\
		$(LIB_DIR)ft_strdel.c $(LIB_DIR)ft_strdup.c	$(LIB_DIR)ft_striter.c		\
		$(LIB_DIR)ft_striteri.c $(LIB_DIR)ft_strjoin.c $(LIB_DIR)ft_strlcat.c	\
		$(LIB_DIR)ft_strlen.c $(LIB_DIR)ft_strncat.c $(LIB_DIR)ft_strncmp.c		\
		$(LIB_DIR)ft_strncpy.c $(LIB_DIR)ft_strnequ.c $(LIB_DIR)ft_strnew.c		\
		$(LIB_DIR)ft_strsplit.c	$(LIB_DIR)ft_strstr.c $(LIB_DIR)ft_strsub.c		\
		$(LIB_DIR)ft_strtrim.c $(LIB_DIR)ft_tolower.c $(LIB_DIR)ft_free_array.c	\
		$(LIB_DIR)ft_iswhitespace.c $(LIB_DIR)ft_abs.c $(LIB_DIR)ft_strnstr.c	\
		$(LIB_DIR)ft_strrchr.c $(LIB_DIR)ft_toupper.c $(LIB_DIR)ft_abs_long.c	\
		$(LIB_DIR)ft_lstadd_back.c $(LIB_DIR)ft_strndup.c $(LIB_DIR)ft_isupper.c\
		$(LIB_DIR)ft_itoa_base.c $(LIB_DIR)ft_itoa_base_unsigned.c				\
		$(LIB_DIR)ft_split_whitespace.c $(LIB_DIR)ft_array_len.c				\
		$(LIB_DIR)ft_print_array.c $(LIB_DIR)ft_is_dir.c						\
		$(LIB_DIR)ft_is_valid_path.c $(LIB_DIR)ft_string_insert.c
GNL = $(GNL_DIR)get_next_line.c $(GNL_DIR)gnl_helpers.c
PRF = $(PRF_DIR)conversion_control.c $(PRF_DIR)ft_printf.c $(PRF_DIR)set_flags.c\
		$(PRF_DIR)print_result.c $(PRF_DIR)hash_flag.c $(PRF_DIR)flag_control.c	\
		$(PRF_DIR)numeric_conversion.c $(PRF_DIR)width_precision.c				\
		$(PRF_DIR)plus_flag.c $(PRF_DIR)handle_double.c $(PRF_DIR)add_sign.c	\
		$(PRF_DIR)ft_printf_putstr.c $(PRF_DIR)double_helpers.c					\
		$(PRF_DIR)double_helpers2.c	$(PRF_DIR)signed_conversion_handlers.c		\
		$(PRF_DIR)unsigned_conversion_handlers.c $(PRF_DIR)n_conversion.c		\
		$(PRF_DIR)set_conv_type.c $(PRF_DIR)colours.c $(PRF_DIR)zero_flag.c		\
		$(PRF_DIR)chop_chop.c $(PRF_DIR)print_result_functions.c				\
		$(PRF_DIR)z_conversions.c $(PRF_DIR)ft_printf_control.c
LIB_OBJ = $(LIB:.c=.o)  
GNL_OBJ = $(GNL:.c=.o)  
PRF_OBJ = $(PRF:.c=.o)  

all: $(NAME)
	@echo libft compiled

$(NAME):
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) -C $(PRF_DIR)
	@ar rcs $(NAME) $(LIB_OBJ) $(GNL_OBJ) $(PRF_OBJ)

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
