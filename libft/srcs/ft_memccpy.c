/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:25:33 by amann             #+#    #+#             */
/*   Updated: 2021/12/03 16:20:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	stop;

	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	stop = (unsigned char) c;
	if (n <= 0)
		return (NULL);
	while (n > 0 && *s != stop)
	{
		*d++ = *s++;
		n--;
	}
	if (*s == stop)
	{
		*d++ = *s++;
		return (d);
	}
	else
		return (NULL);
}
