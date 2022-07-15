# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 12:00:56 by amann             #+#    #+#              #
#    Updated: 2022/07/15 16:28:37 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c gnl_helpers.c
OBJ = get_next_line.o gnl_helpers.o
LEAKS = -g -fsanitize=address

all:
	@gcc $(FLAGS) -c $(SRCS)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
