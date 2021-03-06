/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:27:31 by amann             #+#    #+#             */
/*   Updated: 2021/12/01 17:28:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f' || c == '\n')
		return (1);
	return (0);
}
