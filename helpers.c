/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:33:57 by amann             #+#    #+#             */
/*   Updated: 2022/06/22 17:35:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t	array_len(char **arr)
{
	size_t	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int		get_env_idx(t_sh *shell, char *str)
{
	int		i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], str, len) == 0)
			return (i);		
		i++;
	}
	return (-1);
}
