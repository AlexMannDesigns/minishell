/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:38:59 by amann             #+#    #+#             */
/*   Updated: 2021/12/04 16:19:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*res_malloc(char const *s, int pos, char c)
{
	int		len;
	char	*str;
	int		i;

	len = 0;
	while (s[pos + len] != c && s[pos + len] != '\0')
		len++;
	str = (char *) ft_memalloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[pos + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**final_res_malloc(char **res, const char *s)
{
	int		i;
	char	**final_res;

	i = 0;
	while (res[i] != NULL)
		i++;
	final_res = (char **) ft_memalloc((i + 1) * sizeof(char *));
	if (!final_res)
	{
		ft_free_array((void ***)(&final_res), i);
		return (NULL);
	}
	i = 0;
	while (res[i] != NULL)
	{
		final_res[i] = ft_strdup(res[i]);
		i++;
	}
	final_res[i] = NULL;
	ft_free_array((void ***)(&res), (ft_strlen(s) / 2));
	return (final_res);
}

char	**ft_strsplit(char const *s, char c)
{
	int		pos;
	int		i;
	char	**res;
	char	**final_res;

	if (!s)
		return (NULL);
	pos = 0;
	i = 0;
	res = (char **) ft_memalloc(((ft_strlen(s) / 2) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[pos] != '\0')
	{
		if (s[pos] != c)
		{
			res[i] = res_malloc(s, pos, c);
			pos = pos + (ft_strlen(res[i]) - 1);
			i++;
		}
		pos++;
	}
	res[i] = NULL;
	final_res = final_res_malloc(res, s);
	return (final_res);
}
