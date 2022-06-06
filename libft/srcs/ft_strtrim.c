/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:22 by amann             #+#    #+#             */
/*   Updated: 2021/11/15 17:16:22 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*strtrim_helper(char const *s, char *res, size_t len, size_t st)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		res[i] = s[st + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s)
{
	size_t	st;
	size_t	end;
	size_t	len;
	char	*res;

	if (!s)
		return (NULL);
	st = 0;
	while ((s[st] == ' ' || s[st] == '\n' || s[st] == '\t') && s[st] != '\0')
		st++;
	end = ft_strlen(s) - 1;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
	{
		if (end == 0)
			return ("");
		end--;
	}
	len = end - st + 1;
	res = (char *) malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (strtrim_helper(s, res, len, st));
}
