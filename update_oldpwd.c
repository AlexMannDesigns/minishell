/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_oldpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:37:25 by amann             #+#    #+#             */
/*   Updated: 2022/07/13 15:40:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_env_to_new(t_sh *shell, char **new_env)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		new_env[i] = ft_strdup(shell->env[i]);
		if (!new_env[i])
		{
			ft_free_array((void ***) &new_env, ft_array_len(new_env));
			return (0);
		}
		i++;
	}
	ft_free_array((void ***) &shell->env, ft_array_len(shell->env));
	return (1);
}

/* strjoin can safely return NULL pointer here */

static int	create_oldpwd(t_sh *shell, char *cwd)
{
	size_t	len;
	char	**new_env;

	len = ft_array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	if (shell->env)
	{
		if (!copy_env_to_new(shell, new_env))
			return (0);
	}
	new_env[len] = ft_strjoin("OLDPWD=", cwd);
	shell->env = new_env;
	return (1);
}

void	update_oldpwd(t_sh *shell)
{
	int		i;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return ;
	i = get_env_idx(shell, "OLDPWD");
	if (i == -1)
	{
		if (!create_oldpwd(shell, cwd))
			return ;
	}
	else
	{
		ft_strdel(&(shell->env[i]));
		shell->env[i] = ft_strjoin("OLDPWD=", cwd);
	}
}
