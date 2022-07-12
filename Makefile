# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 13:23:10 by amann             #+#    #+#              #
#    Updated: 2022/07/12 12:01:31 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = minishell
FLAGS = -Wall -Werror -Wextra -std=c99 -pedantic -O3
#-fsanitize=address -g
SRCS = check_user_dir.c create_arg_list.c dollar_next_middle_start_end.c		\
		environment.c expand_tildes.c expand_dollars.c handle_cd.c				\
		handle_echo.c handle_env.c handle_exit.c handle_quotes.c				\
		handle_setenv.c helpers.c initialise_shell.c main.c parser.c			\
		print_error.c update_env.c update_dollar_arg.c update_oldpwd.c			\
		validate_command.c
OBJ = $(SRCS:%.c=%.o)
HEADER = -I includes/minishell.h
LIB_DIR = libft/

#rules
all: $(NAME)

$(NAME): libft_make $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft
#-fsanitize=address -g

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
