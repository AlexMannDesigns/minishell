/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:05:24 by amann             #+#    #+#             */
/*   Updated: 2022/03/15 15:42:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	uc_s1 = (unsigned char *) s1;
	uc_s2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (*(uc_s1 + i) == *(uc_s2 + i))
			i++;
		else
			return (*(uc_s1 + i) - *(uc_s2 + i));
	}
	return (0);
}
