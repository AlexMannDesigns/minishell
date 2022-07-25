/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:42:37 by amann             #+#    #+#             */
/*   Updated: 2022/07/25 14:43:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_is_dir(char *path)
{
	struct stat	temp;

	if (lstat(path, &temp) == -1)
		return (0);
	else if ((temp.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}
