/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:58:46 by amann             #+#    #+#             */
/*   Updated: 2022/07/05 15:18:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	remove_env_var(t_sh *shell, int idx)
{
	int		i;
	int		j;
	int		k;
	size_t	len;
	char	**new_env;

	len = array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * len);
	if (!new_env)
		return ;
	i = idx;
	j = 0;
	k = 0;
	while (shell->env[j])
	{
		if (j == i)
		{	
			k++;
			i = -1;
		}
		else
		{
			new_env[j] = shell->env[k];
			j++;
			k++;
		}
	}
	ft_strdel(&(shell->env[idx]));
	free(shell->env);
	shell->env = new_env;
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
		if (ft_strchr(shell->arg_list[i], '=') == NULL)
			break ;
		update_env_control(shell, i);
		i++;	
	}
}
