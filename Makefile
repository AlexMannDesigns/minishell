# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 13:23:10 by amann             #+#    #+#              #
#    Updated: 2022/07/18 15:02:26 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = minishell
FLAGS = -Wall -Werror -Wextra -ansi -std=c99 -pedantic -O3 -g
#-fsanitize=address -g
SRCS =  builtin_control.c check_user_dir.c count_quote_args.c create_arg_list.c	\
		dollar_next_middle_start_end.c environment.c expand_tildes.c			\
		expand_dollars.c handle_cd.c handle_echo.c handle_env.c handle_exit.c	\
		handle_quotes.c handle_setenv.c helpers.c initialise_shell.c main.c		\
		parser.c print_error.c update_env.c update_dollar_arg.c update_oldpwd.c	\
		validate_command.c
OBJ = $(SRCS:%.c=%.o)
HEADER = -I includes/minishell.h
LIB_DIR = libft/

#rules
all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

%.o:%.c
	gcc $(FLAGS) $(HEADER) -c $< -o $@

libft/libft.a:
	@echo compiling libft...
	@$(MAKE) -C $(LIB_DIR)

clean:
	@echo deleting objects...
	@/bin/rm -f $(OBJ)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@echo deleting executable...
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean re fclean 
