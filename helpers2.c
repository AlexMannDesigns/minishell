/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:10:39 by amann             #+#    #+#             */
/*   Updated: 2022/07/28 15:58:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	update_existing_env(t_sh *shell, char *str, int env_idx)
{
	ft_strdel(&(shell->env[env_idx]));
	shell->env[env_idx] = ft_strdup(str);
	if (!shell->env[env_idx])
		return (0);
	return (1);
}

/* strdup in this function does not need malloc protection */

int	add_new_env_var(t_sh *shell, char *str)
{
	size_t	len;
	size_t	j;
	char	**new_env;

	len = ft_array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	j = 0;
	if (shell->env)
	{
		while (shell->env[j])
		{
			new_env[j] = shell->env[j];
			j++;
		}
		free(shell->env);
	}
	new_env[j] = ft_strdup(str);
	shell->env = new_env;
	return (1);
}

size_t	var_name_len(char *dollar)
{
	size_t	len;

	len = 0;
	while (dollar[len] && dollar[len] != '$')
		len++;
	return (len);
}

char	*copy_args_helper(char *cli, t_copy_args args)
{
	if (args.len != 0)
		return (ft_strndup(cli + args.cursor, args.len));
	else
		return (ft_strdup("\0"));
}