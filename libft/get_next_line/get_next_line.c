/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:06:31 by amann             #+#    #+#             */
/*   Updated: 2022/03/15 12:18:49 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_file(int fd, t_lines **lst)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*temp;

	ft_bzero(buf, BUFF_SIZE + 1);
	ret = read(fd, buf, BUFF_SIZE);
	while (ret)
	{
		if (ret == -1)
			return (-1);
		if (!((*lst)->str))
			(*lst)->str = ft_strdup(buf);
		else
		{
			temp = ft_strdup((*lst)->str);
			free((*lst)->str);
			(*lst)->str = ft_strjoin(temp, buf);
			free(temp);
		}
		if (ft_strchr((*lst)->str, '\n'))
			return (1);
		ft_bzero(buf, BUFF_SIZE + 1);
		ret = read(fd, buf, BUFF_SIZE);
	}
	return (0);
}

static int	ft_set_line(char **line, t_lines **lst, int end)
{
	size_t	i;
	char	*temp;

	if (((*lst)->str && (end && ft_strlen((*lst)->str))) || !end)
	{
		i = 0;
		while ((*lst)->str[i] != '\n' && (*lst)->str[i] != '\0')
			i++;
		*line = (char *) ft_memalloc((sizeof(char) * i) + 1);
		if (!(*line))
			return (-1);
		ft_strncpy(*line, (*lst)->str, i);
		if (!end)
		{
			temp = ft_strdup(ft_strchr((*lst)->str, '\n'));
			free((*lst)->str);
			(*lst)->str = ft_strdup(temp + 1);
			free(temp);
			return (1);
		}
		ft_strdel(&(*lst)->str);
		return (1);
	}
	else
		return (0);
}

static void	find_node(t_lines **my_list, int fd, t_lines **front)
{
	t_lines	*new;

	*front = *my_list;
	while (*my_list)
	{
		if ((*my_list)->filedes == fd)
			return ;
		else if ((*my_list)->next == NULL)
			break ;
		*my_list = (*my_list)->next;
	}
	new = (t_lines *) malloc(sizeof(t_lines));
	if (!new)
		return ;
	new->filedes = fd;
	new->str = NULL;
	new->next = NULL;
	if (!(*my_list))
	{
		*my_list = new;
		*front = *my_list;
		return ;
	}
	(*my_list)->next = new;
	*my_list = (*my_list)->next;
}

int	get_next_line(const int fd, char **line)
{
	static t_lines	*my_list;
	t_lines			*front;
	int				end;
	int				ret_val;
	int				read_res;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	end = 0;
	find_node(&my_list, fd, &front);
	if (my_list->str && ft_strchr(my_list->str, '\n'))
	{
		ret_val = ft_set_line(line, &my_list, end);
		my_list = front;
		return (ret_val);
	}
	read_res = ft_read_file(fd, &my_list);
	if (read_res == -1)
		return (-1);
	else if (!read_res)
		end = 1;
	ret_val = ft_set_line(line, &my_list, end);
	my_list = front;
	return (ret_val);
}
