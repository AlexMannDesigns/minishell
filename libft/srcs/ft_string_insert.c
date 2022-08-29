/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:52:44 by amann             #+#    #+#             */
/*   Updated: 2022/08/29 16:21:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	overwrite_valid(char *orig, int idx, size_t overwrite)
{
	size_t	len;

	len = ft_strlen(orig);
	if ((overwrite + (size_t) idx) > len)
		return (0);
	return (1);
}

static char	*free_mem_end(char *start)
{
	if (start)
		free(start);
	return (NULL);
}

static char	*connect_strings(char *start, char *insert, char *end)
{
	char	*start_plus_insert;
	char	*res;

	start_plus_insert = ft_strjoin(start, insert);
	if (!start_plus_insert)
	{
		free(start);
		free(end);
		return (NULL);
	}
	res = ft_strjoin(start_plus_insert, end);
	free(start_plus_insert);
	return (res);
}

/* the overwrite param determines whether we overwrite the char at the idx,
 * or place the insert string before it. If 0, no overwrite happens,
 * otherwise, the number determines the number of characters overwritten.
 *
 * We can return res without malloc protection beforehand, because it is
 * fine for this function to return a NULL pointer
 */

char	*ft_string_insert(char *orig, char *insert, int idx, size_t overwrite)
{
	char	*start;
	char	*end;
	char	*res;

	if (!orig || !insert || !overwrite_valid(orig, idx, overwrite))
		return (NULL);
	start = NULL;
	if (idx > 0)
	{
		start = ft_strndup(orig, idx);
		if (!start)
			return (NULL);
	}
	end = ft_strdup(orig + idx + overwrite);
	if (!end)
		return (free_mem_end(start));
	if (start)
		res = connect_strings(start, insert, end);
	else
		res = ft_strjoin(insert, end);
	if (start)
		free(start);
	free(end);
	return (res);
}
