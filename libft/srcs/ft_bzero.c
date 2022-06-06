/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:41:27 by amann             #+#    #+#             */
/*   Updated: 2022/03/15 15:43:18 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;

	uc_s1 = (unsigned char *) s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		*(uc_s1 + i) = '\0';
		i++;
	}	
}
