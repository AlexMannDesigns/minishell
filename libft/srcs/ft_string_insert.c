/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:52:44 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 15:27:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*free_and_ret(char *start, char *end, char *s_p_i, int option)
{
	if (option == 1)
		free(start);
	if (option == 2)
	{
		free(start);
		free(end);
	}
	if (option == 3)
	{
		free(start);
		free(end);
		free(s_p_i);
	}
	return (NULL);
}

/* the overwrite param determines whether we overwrite the char at the idx,
 * or place the insert string before it. If 0, no overwrite happens,
 * otherwise, the number determines the number of characters overwritten.
 */

char	*ft_string_insert(char *orig, char *insert, int idx, size_t overwrite)
{
	char	*start;
	char	*end;
	char	*start_plus_insert;
	char	*res;

	if (!orig || !insert)
		return (NULL);
	start = ft_strndup(orig, idx);
	if (!start)
		return (NULL);
	end = ft_strdup(orig + idx + overwrite);
	if (!end)
		return (free_and_ret(start, NULL, NULL, 1));
	start_plus_insert = ft_strjoin(start, insert);
	if (!start_plus_insert)
		return (free_and_ret(start, end, NULL, 2));
	res = ft_strjoin(start_plus_insert, end);
	if (!res)
		return (free_and_ret(start, end, start_plus_insert, 3));
	free_and_ret(start, end, start_plus_insert, 3);
	return (res);
}
