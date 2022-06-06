/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:09:07 by amann             #+#    #+#             */
/*   Updated: 2022/03/16 19:28:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;

	uc_s1 = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (*(uc_s1 + i) == (unsigned char)c)
			return ((void *)(uc_s1 + i));
		i++;
	}
	return (NULL);
}
