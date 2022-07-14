/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:42:19 by amann             #+#    #+#             */
/*   Updated: 2022/07/14 17:29:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_loop(const char *s, va_list lst, int *ret)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%' || s[i] == '{')
		{
			ft_printf_putchar(s + count, i - count, ret);
			if (s[i + 1] == '\0' && s[i] == '%')
				return ;
			if (s[i] == '{')
				check_colour(s + i, &i, ret);
			else
				ft_printf_ctrl((s + i + 1), lst, &i, ret);
			count = i + 1;
		}
		i++;
	}
	ft_printf_putchar(s + count, i - count, ret);
}

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	int		ret;

	va_start(lst, s);
	ret = 0;
	ft_printf_loop(s, lst, &ret);
	va_end(lst);
	return (ret);
}
