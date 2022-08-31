/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_plus_minus_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:06:57 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 18:12:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tilde_plus_minus_expansion(t_sh *shell, size_t i)
{
	int		idx;
	char	*res;

	if ((shell->cli)[i + 1] == '+')
	{
		idx = get_env_idx(shell, "PWD");
		if (idx == -1)
			return (NULL);
		res = ft_strdup((shell->env[idx]) + 4);
	}
	else
	{
		idx = get_env_idx(shell, "OLDPWD");
		if (idx == -1)
			return (NULL);
		res = ft_strdup((shell->env[idx]) + 7);
	}
	return (res);
}
