/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:26:23 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 16:27:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../includes/libft.h"
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

typedef struct a_list
{
	int				filedes;
	char			*str;
	struct a_list	*next;
}					t_lines;

int	get_next_line(const int fd, char **line);
int	read_file_helper(t_lines **lst, char *buf);
int	set_line_helper(t_lines **lst);
#endif
