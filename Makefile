# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 13:23:10 by amann             #+#    #+#              #
#    Updated: 2022/08/29 14:26:33 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = minishell
FLAGS = -Wall -Werror -Wextra -std=c99 -pedantic -O3 -g
SRCS =  builtin_control.c check_user_dir.c copy_args_control.c create_arg_list.c\
		expand_dollars.c expand_tildes.c 										\
		handle_cd.c handle_echo_exit.c handle_env.c handle_setenv_unsetenv.c	\
		helpers.c helpers2.c initialise_shell.c main.c print_error.c			\
		print_header.c tilde_plus_minus_expansion.c tilde_var_assignment.c		\
		tilde_username_expansion.c tilde_check_plus_minus_expansion.c			\
		tilde_get_home_path.c													\
		update_dollar_arg.c update_env.c update_oldpwd.c update_underscore.c	\
		validate_command.c 
OBJ = $(SRCS:%.c=%.o)
HEADER = -I includes/
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
