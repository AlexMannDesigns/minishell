/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_user_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:47:10 by amann             #+#    #+#             */
/*   Updated: 2022/07/05 16:51:49 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_users(char *str, size_t len)
{
	DIR				*users;
	struct dirent	*current_obj;
	int				res;

	res = FALSE;
	users = opendir("/Users");
	if (!users)
		return (res);
	current_obj = readdir(users);
	while (current_obj != NULL)
	{
		if (ft_strncmp(current_obj->d_name, str + 1, len - 1) == 0)
		{
			res = TRUE;
			break ;
		}
		current_obj = readdir(users);
	}
	closedir(users);
	return (res);
}
