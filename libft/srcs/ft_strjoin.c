/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:40:59 by amann             #+#    #+#             */
/*   Updated: 2022/01/03 12:24:17 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	total;
	size_t	i;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len1 = (ft_strlen(s1));
	len2 = (ft_strlen(s2));
	total = len1 + len2;
	res = (char *) malloc((total + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < total)
	{
		if (i < len1)
			res[i] = s1[i];
		else
			res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	return (res);
}
