/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_user_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:47:10 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 17:09:18 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_users(char *str)
{
	DIR				*users;
	struct dirent	*current_obj;
	int				res;
	size_t			len;

	res = FALSE;
	users = opendir("/Users");
	if (!users)
		return (res);
	current_obj = readdir(users);
	while (current_obj != NULL)
	{
		len = ft_strlen(current_obj->d_name);
		if (ft_strncmp(current_obj->d_name, str + 1, len) == 0)
		{
			res = TRUE;
			break ;
		}
		current_obj = readdir(users);
	}
	closedir(users);
	return (res);
}
