# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 12:00:56 by amann             #+#    #+#              #
#    Updated: 2022/03/19 18:08:32 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c
OBJ = get_next_line.o
LEAKS = -g -fsanitize=address

all:
	@gcc $(FLAGS) -c $(SRCS)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
