/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:48:07 by amann             #+#    #+#             */
/*   Updated: 2022/01/10 11:30:37 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && !ft_iswhitespace(str[i]) && \
			!(str[i] == '+' && ft_isdigit(str[i + 1])))
		{
			if (str[i] == '-' && ft_isdigit(str[i + 1]))
				sign = -1;
			else
				return (0);
		}
		if (ft_isdigit(str[i]))
			res = (res * 10) + (str[i] - 48);
		if (ft_isdigit(str[i]) && !ft_isdigit(str[i + 1]))
			break ;
		i++;
	}
	return (res * sign);
}
