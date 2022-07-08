/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_oldpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:37:25 by amann             #+#    #+#             */
/*   Updated: 2022/07/08 18:08:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	copy_env_to_new(t_sh *shell, char **new_env)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
}

void	update_oldpwd(t_sh *shell)
{
	int		i;
	size_t	len;
	char	**new_env;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	i = get_env_idx(shell, "OLDPWD");
	if (i == -1)
	{
		len = array_len(shell->env);
		new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
		if (!new_env)
			return ;
		if (shell->env)
			copy_env_to_new(shell, new_env);
		new_env[len] = ft_strjoin("OLDPWD=", cwd);
		if (!new_env[len])
			return ;
		shell->env = new_env;
	}
	else
	{
		ft_strdel(&(shell->env[i]));
		shell->env[i] = ft_strjoin("OLDPWD=", cwd);
	}
}
