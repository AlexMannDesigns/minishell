/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_multi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:32:22 by amann             #+#    #+#             */
/*   Updated: 2022/07/13 15:41:29 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	word_count(const char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
		{
			count++;
			while (str[i] && !ft_iswhitespace(str[i]))
				i++;
		}
		i++;
	}
	return (count);
}

static size_t	substrlen(const char *str, size_t i)
{
	size_t	len;

	len = 0;
	while (str[i] && !ft_iswhitespace(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static void	ft_split_ws_loop(const char *str, char ***arr)
{
	size_t	i;
	size_t	len;
	size_t	idx;

	i = 0;
	idx = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
		{
			len = substrlen(str, i);
			(*arr)[idx] = ft_strndup(str + i, len);
			if (!(*arr)[idx])
			{
				ft_freearray((void ***) arr, ft_array_len(*arr));
				return ;
			}
			i += len;
			idx++;
		}
		else
			i++;
	}
}

char	**ft_split_whitespace(const char *str)
{
	char	**arr;
	size_t	wc;

	wc = word_count(str);
	if (!wc)
		return (NULL);
	arr = (char **) ft_memalloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	ft_split_ws_loop(str, &arr);
	return (arr);
}
