/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:24:03 by amann             #+#    #+#             */
/*   Updated: 2021/12/01 13:33:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*positive_res_malloc(char *s, int len)
{
	char	*res;
	int		i;

	res = (char *) ft_memalloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

static char	*negative_res_malloc(char *s, int len, int min)
{
	char	*res;
	int		i;

	res = (char *) ft_memalloc((len + 2) * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '-';
	i = 1;
	while (s[i - 1] != '\0')
	{
		if (i == 10 && min == 1)
			res[i] = '8';
		else
			res[i] = s[i - 1];
		i++;
	}	
	return (res);
}

static char	*itoa_recursion(char *dest, int n)
{
	if (n >= 10)
		dest = itoa_recursion(dest, n / 10);
	*dest++ = 48 + (n % 10);
	return (dest);
}

char	*ft_itoa(int n)
{
	char	s[20];
	char	*res;
	size_t	len;
	int		sign;
	int		min;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		if (n == -2147483648)
		{
			min = 1;
			n = 2147483647;
		}
		else
			n = n * -1;
	}
	*itoa_recursion(s, n) = '\0';
	len = ft_strlen(s);
	if (sign == 1)
		res = positive_res_malloc(s, len);
	else
		res = negative_res_malloc(s, len, min);
	return (res);
}
