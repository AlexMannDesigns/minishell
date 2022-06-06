/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_conversions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:32:42 by amann             #+#    #+#             */
/*   Updated: 2022/03/10 15:43:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_zd(ssize_t x, t_flags *flag)
{
	char	*res;
	int		min_flag;

	min_flag = FALSE;
	if (x < 0)
		flag->conv.neg = TRUE;
	if (x == 0)
		flag->nil = TRUE;
	if (x == LONG_MIN)
	{
		min_flag = TRUE;
		x += 1;
	}
	res = ft_itoa_base(ft_abs_long((long long) x), BASE_TEN);
	if (flag->conv.neg)
		res = add_sign(res);
	if (min_flag)
		res[ft_strlen(res) - 1] = '8';
	return (res);
}

char	*handle_zu(size_t x, t_flags *flag, int base)
{
	if (x == 0)
		flag->nil = TRUE;
	return (ft_itoa_base_unsigned((unsigned long long)x, base));
}
