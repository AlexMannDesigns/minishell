/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:58:46 by amann             #+#    #+#             */
/*   Updated: 2022/07/28 15:35:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	remove_env_var_loop(t_sh *shell, int idx, char ***new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i == idx)
		{
			j++;
			idx = -1;
		}
		else
		{
			(*new_env)[i] = shell->env[j];
			i++;
			j++;
		}
	}
}

static void	remove_env_var(t_sh *shell, int idx)
{
	size_t	len;
	char	**new_env;

	len = ft_array_len(shell->env);
	if (len > 1)
	{
		new_env = (char **) ft_memalloc(sizeof(char *) * len);
		if (!new_env)
			return ;
		remove_env_var_loop(shell, idx, &new_env);
		ft_strdel(&(shell->env[idx]));
		free(shell->env);
		shell->env = new_env;
	}
	else
	{
		ft_strdel(&(shell->env[0]));
		free(shell->env);
		shell->env = NULL;
	}
}

void	handle_unsetenv(t_sh *shell)
{
	int	i;
	int	idx;

	i = 1;
	while (shell->arg_list[i])
	{
		idx = get_env_idx(shell, shell->arg_list[i]);
		if (idx != -1)
			remove_env_var(shell, idx);
		i++;
	}
}

void	handle_setenv(t_sh *shell)
{
	int	i;

	i = 1;
	while (shell->arg_list[i])
	{
		update_env_control(shell, i, FALSE);
		i++;
	}
}
