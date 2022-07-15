/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:26:22 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 16:27:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	set_line_helper(t_lines **lst)
{
	char	*temp;

	temp = ft_strdup(ft_strchr((*lst)->str, '\n'));
	if (!temp)
		return (0);
	free((*lst)->str);
	(*lst)->str = ft_strdup(temp + 1);
	free(temp);
	if (!(*lst)->str)
		return (0);
	return (1);
}

int	read_file_helper(t_lines **lst, char *buf)
{
	char	*temp;

	if (!((*lst)->str))
	{
		(*lst)->str = ft_strdup(buf);
		if (!(*lst)->str)
			return (0);
	}
	else
	{
		temp = ft_strdup((*lst)->str);
		if (!temp)
			return (0);
		free((*lst)->str);
		(*lst)->str = ft_strjoin(temp, buf);
		free(temp);
		if (!(*lst)->str)
			return (0);
	}
	return (1);
}
