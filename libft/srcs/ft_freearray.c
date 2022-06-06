/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:43:03 by amann             #+#    #+#             */
/*   Updated: 2022/03/18 16:09:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_freearray(void ***arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i <= size)
	{
		if (*((*arr) + i))
		{
			free(*((*arr) + i));
			*((*arr) + i) = NULL;
		}
		i++;
	}
	free(*arr);
	*arr = NULL;
}
