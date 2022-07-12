/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:33:57 by amann             #+#    #+#             */
/*   Updated: 2022/07/12 19:04:26 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_whitespaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**copy_arr(char **arr)
{
	char	**res;
	size_t	len;
	size_t	i;

	if (!arr)
		return (NULL);
	len = array_len(arr);
	res = (char **) ft_memalloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		if (!res[i])
		{
			ft_freearray((void ***) &res, array_len(res));
			return (NULL);
		}
		i++;
	}
	return (res);
}

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		ft_putendl(arr[i++]);
}

size_t	array_len(char **arr)
{
	size_t	res;

	if (!arr)
		return (0);
	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int	get_env_idx(t_sh *shell, char *str)
{
	int		i;
	size_t	len;
	char	*str_plus_equals;

	str_plus_equals = ft_strjoin(str, "=");
	if (!str_plus_equals || !shell->env)
	{
		ft_strdel(&str_plus_equals);
		return (-1);
	}
	len = ft_strlen(str_plus_equals);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], str_plus_equals, len) == 0)
		{
			ft_strdel(&str_plus_equals);
			return (i);
		}
		i++;
	}
	ft_strdel(&str_plus_equals);
	return (-1);
}
