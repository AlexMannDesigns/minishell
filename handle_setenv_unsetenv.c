/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:58:46 by amann             #+#    #+#             */
/*   Updated: 2022/08/31 14:41:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
 * Removing environment variables is a little more complicated then adding.
 * The main reason is that we need to move all the subsequent pointers up an
 * index if we are deleting a variable from anywhere other than the end of
 * the environment array.
 *
 * Calling in a loop allows us to remove multiple variables at a time.
 */

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

/*
 * Perhaps the simplest builtin in the project. We can use thhe update_env
 * function from our env handling, passing a flag to make sure we have valid
 * variable names. As these will be permanent changes, we need to follow
 * naming conventions strictly.
 *
 * We call in a loop to allow us to add multiple variables in a loop.
 */

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
