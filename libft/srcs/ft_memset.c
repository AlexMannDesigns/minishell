/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:06:44 by amann             #+#    #+#             */
/*   Updated: 2022/03/16 19:28:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*uc_s1;

	uc_s1 = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		*(uc_s1 + i) = c;
		i++;
	}
	return (b);
}
