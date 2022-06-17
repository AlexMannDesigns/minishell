# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 13:23:10 by amann             #+#    #+#              #
#    Updated: 2022/06/17 13:18:51 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = minishell
FLAGS = -Wall -Werror -Wextra -ansi -std=c99 -pedantic -O3
SRCS = array_len.c environment.c main.c parser.c validate_command.c
OBJ = $(SRCS:%.c=%.o)
HEADER = -I includes/minishell.h
LIB_DIR = libft/

#rules
all: $(NAME)

$(NAME): libft_make $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

%.o: %.c
	@gcc $(FLAGS) $(HEADER) -c $< -o $@

libft_make:
	@$(MAKE) -C $(LIB_DIR)

clean:
	@/bin/rm -f $(OBJ)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean re fclean libft_make
