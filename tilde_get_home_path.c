/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_get_home_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:24:05 by amann             #+#    #+#             */
/*   Updated: 2022/08/29 14:26:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde_get_home_path(t_sh *shell, char **home)
{
	int		idx;

	idx = get_env_idx(shell, "HOME");
	if (idx == -1)
	{
		*home = NULL;
		return ;
	}
	*home = ft_strchr(shell->env[idx], '=') + 1;
}
