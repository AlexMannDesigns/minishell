/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:25:19 by amann             #+#    #+#             */
/*   Updated: 2022/07/05 15:01:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	get_equals_idx(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	update_existing_env(t_sh *shell, char *str, int env_idx)
{
	ft_strdel(&(shell->env[env_idx]));
	shell->env[env_idx] = ft_strdup(str);
	if (!shell->env[env_idx])
		return (0);
	return (1);
}

int	add_new_env_var(t_sh *shell, char *str)
{
	size_t	len;
	size_t	j;
	char	**new_env;
	
	len = array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	j = 0;
	while (shell->env[j])
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(str); //if this malloc fails, this will not cause problems.
	free(shell->env); //I want to free the pointers, but not what they are pointing to, think this is ok...
	shell->env = new_env;
	return (1);
}

int	update_env_control(t_sh *shell, size_t i)
{
	char	*str;
	char	*var_name;
	int		env_idx;
	int		equals_idx;
	int		error;

	str = shell->arg_list[i];
	equals_idx = get_equals_idx(str);
	if (equals_idx == 0 || equals_idx == -1)
		return (0);
	var_name = ft_strndup(str, equals_idx);
	env_idx = get_env_idx(shell, var_name);
	free(var_name);
	if (env_idx != -1)
		error = update_existing_env(shell, str, env_idx);
	else
		error = add_new_env_var(shell, str);
	if (!error)
		return (0);
	return (1);
}
